#include"si_global.h"
#include"linklist.h"
#include"sistring.h"
#include"stack.h"
#include"element.h"
#include"selfclosedlabelchecker.h"
#include"segmentationer.h"


namespace SI
{	
	using std::ofstream;
	using std::ifstream;
	using std::string;
	using std::endl;
	using std::cout;

	const int MAX_WEB_NUM = 105;
	const int CONT_NUM = 10;
	bool readline(FILE* infile, char* s)
	{
		char t;
		int len = 0;
		for (t = getc(infile); SIString::isenter(t); t = getc(infile));
		while (SIString::isblank(t)) t = getc(infile);
		if (t == EOF) return false;
		for (; !(SIString::isenter(t)) && t != EOF; t = getc(infile)) s[len++] = t;
		s[len++] = '\0';
		if (t == EOF) return false;
		return true;
	}

	void extractInfo(char* infilename, ofstream& fout)
	{
		bool in_ignore_js_op = false;
		bool in_z = false;
		bool in_t_f = false;
		bool in_authi = false;
		bool in_ts_z_h1 = false;
		bool find_tltype = false;
		bool find_tstype = false;
		bool find_ttitle = false;
		bool find_tcontent = false;
		bool find_tauthi = false;
		bool find_tdate = false;
		bool find_ttype = false;
		int div_z_cnta = 0, div_authi_cnt = 0, div_t_f_cnt = 0;
		enum
		{
			LTYPE = 0, STYPE, TITLE, CONTENT, AUTHI, DATE, TYPE
		};
		SIString ans[CONT_NUM];

		Stack<Element> stk;
		FILE* fin = fopen(infilename, "r");
		char *str = new char[4096];
		SIString sistr;
		Element ele;
		SIString* pname;
		while (readline(fin, str))
		{
			if (str[0] == '<')
			{
				readline(fin, str);
				sistr.fromCstr(str);
				sistr.transComma();
				ele.assign(Element::LABEL, sistr);
				readline(fin, str);
			}
			else
			{
				sistr.assign(str);
				sistr.transComma();
				ele.assign(Element::CONTENT, sistr);
			}
			if (ele.type == Element::LABEL)
			{
				if (SelfClosedLabelChecker::check(ele.contents)) continue;
				pname = &(ele.contents);
				if ((*pname)[0] == '/')
				{
					while ((!stk.empty()) && stk.top().contents != pname->substring(1, pname->getsize() - 1))
					{
						if (stk.top().properties[SIString("class")] == SIString("z"))
							in_z = false;
						if (stk.top().properties[SIString("class")] == SIString("t_f"))
							in_t_f = false;
						if (stk.top().properties[SIString("class")] == SIString("authi"))
							in_authi = false;
						if (stk.top().properties[SIString("class")] == SIString("ts z h1"))
							in_ts_z_h1 = false;
						if (stk.top().properties[SIString("class")] == SIString("ignore_js_op"))
							in_ignore_js_op = false;
						stk.pop();
					}
					if (!stk.empty())
					{
						if (stk.top().properties[SIString("class")] == SIString("z"))
							in_z = false;
						if (stk.top().properties[SIString("class")] == SIString("t_f"))
							in_t_f = false;
						if (stk.top().properties[SIString("class")] == SIString("authi"))
							in_authi = false;
						if (stk.top().properties[SIString("class")] == SIString("ts z h1"))
							in_ts_z_h1 = false;
						if (stk.top().contents == SIString("ignore_js_op"))
							in_ignore_js_op = false;
						stk.pop();
					}
				}
				else
				{
					stk.push(ele);
					if (ele.properties[SIString("class")] == SIString("z"))
						in_z = true;
					if (ele.properties[SIString("class")] == SIString("t_f"))
						in_t_f = true;
					if (ele.properties[SIString("class")] == SIString("authi"))
						in_authi = true;
					if (ele.properties[SIString("class")] == SIString("ts z h1"))
						in_ts_z_h1 = true;
					if (ele.contents == SIString("ignore_js_op"))
						in_ignore_js_op = true;

					if (in_z&&ele.contents == SIString("a")) ++div_z_cnta;
					if (in_authi&&ele.contents == SIString("div")) ++div_authi_cnt;
					if (in_t_f&&ele.contents == SIString("td")) ++div_t_f_cnt;
				}
			}
			else
			{
				if (in_ignore_js_op) continue;
				if ((!find_tltype) && in_z && div_z_cnta == 3)
				{
					find_tltype = true;
					ans[LTYPE] += ele.contents;
				}
				if ((!find_tstype) && in_z && div_z_cnta == 4)
				{
					find_tstype = true;
					ans[STYPE] += ele.contents;
				}
				if ((!find_ttitle) && in_z && div_z_cnta == 5)
				{
					find_ttitle = true;
					ans[TITLE] += ele.contents;
				}
				if (in_t_f && div_t_f_cnt == 1)
				{
					ans[CONTENT] += SIString::transEscapeSeq(ele.contents);
					ans[CONTENT] += " ";
				}
				if ((!find_tauthi) && in_authi && div_authi_cnt == 1)
				{
					find_tauthi = true;
					ans[AUTHI] += ele.contents;
				}
				if ((!find_tdate) && in_authi && div_authi_cnt == 2)
				{
					find_tdate = true;
					ans[DATE] += ele.contents;
				}
				if ((!find_ttype) && in_ts_z_h1)
				{
					find_ttype = true;
					ans[TYPE] += ele.contents;
				}
			}
		}

		for (int i = 0; i != 7; ++i)
		{
			if (ans[i].getsize() <= 0) fout << " ";
			else fout << ans[i];
			fout << ",";
		}
		SIStringList res = Segmentationer::doSegmentation(ans[TITLE]);
		for (int k = 0; k < res.size(); ++k)
			fout << res[k] << " ";

		res = Segmentationer::doSegmentation(ans[CONTENT]);
		for (int k = 0; k < res.size(); ++k)
			fout << res[k] << " ";
		fout << endl;

		fclose(fin);
	}

	void initDictionary()
	{
		cout << "allocing buffer" << endl;
		SelfClosedLabelChecker::allocBuff(SelfClosedLabelChecker::BUFF_SIZE);
		Segmentationer::allocBuff(Segmentationer::BUFF_SIZE);
		cout << "loading encoding comparsion list" << endl;
		SIString::init("UnicodeToGBK.csv");
		cout << "loading html label infomation" << endl;
		SelfClosedLabelChecker::init("SelfClosedLabel.list");
		cout << "loading dictionary" << endl;
		Segmentationer::loadDic("dictionary.dic");

	}
	
	void destroyDictionary()
	{
		SelfClosedLabelChecker::destroyBuff();
		Segmentationer::destroyBuff();
	}

	SIStringList divideWords(SIString contents)
	{
		return Segmentationer::doSegmentation(contents);
	}
}
