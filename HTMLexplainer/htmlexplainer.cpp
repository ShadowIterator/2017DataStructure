#define _CRT_SECURE_NO_WARNINGS
#include"si_global.h"
#include"linklist.h"
#include"sistring.h"
#include"stack.h"
#include"element.h"
#include"selfclosedlabelchecker.h"
#include"segmentationer.h"
#include"interface.h"
using namespace std;

using SI::linklist;
using SI::SIchar_t;
using SI::SIsize_t;
using SI::SIString;
using SI::SIStringList;
using SI::Element;
using SI::Stack;
using SI::SelfClosedLabelChecker;
using SI::Segmentationer;
using SI::ACAuto;
typedef std::map<SIString, SIString> mss;
typedef std::map<SIString, SIString>::iterator mssi;

int main()
{
	SI::initDictionary();
	string str, cmd, url;
	ifstream fin;
	ofstream fout;
	fin.open("input\\url.csv");
	fout.open("output\\result.csv");
//	fout.open("result.csv");
//	SI::extractInfo("res.tok",fout);
	
	fin >> str;
	int s, e;
	fout << "\"序号\",\"网址\",\"发帖大类\",\"发帖小类\",\"发帖标题\",\"发帖内容\",\"发帖人\",\"发帖日期\",\"发帖类型\",\"分词结果\"" << endl;
	for (int tot = 0; fin >> str; ++tot)
	{
		cout << "testcase: " << tot << endl;

		for (s = 0; s < str.size() && str[s] != '\"'; ++s);
		for (e = str.size() - 1; e >= 0 && str[e] != '\"'; --e);
		++s; --e;
		if (s >= e) continue;
		url = str.substr(s, e - s + 1);
		cout << "downloading html files: " << url << endl;
		cmd = "SrcFetcher.exe " + url + " res.html";
		system(cmd.c_str());
		cout << "Tokenizing... " << endl;
		cmd = "Tokenizer res.html res.tok";
		system(cmd.c_str());
		cout << "calculating answers... " << endl;
		fout << tot << "," << url << ",";
		SI::extractInfo("res.tok", fout);
	}
	fout.close();
	SI::destroyDictionary();

	return 0;
}