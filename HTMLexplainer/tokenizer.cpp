#define _CRT_SECURE_NO_WARNINGS
#include"si_global.h"
#include"linklist.h"
#include"sistring.h"
#include"stack.h"
#include<cstdio>
using namespace std;
using SI::SIString;
using SI::SIchar_t;
using SI::SIsize_t;

/*
inline wstring transcode(wifstream& wfin)
{
	SIchar_t tt;
	wstring rtn;
	int num = 0;
	rtn.clear();
	wfin >> tt;
	if (tt == L'#')
	{
		for (wfin >> tt; tt != L';'; wfin >> tt) num = num * 10 + tt - L'0';
		rtn += SIchar_t(num);
		wcout << rtn << flush;
	//	wprintf(L"%lc", SIchar_t(num));
	}
	else
	{
		for (; tt != L';'; wfin >> tt) rtn += tt;
		if (rtn == L"quot")
			rtn = L"\"";
		else if (rtn == L"amp")
			rtn = L"&";
		else if (rtn == L"lt")
			rtn = L"<";
		else if (rtn == L"gt")
			rtn = L">";
		else if (rtn == L"nbsp")
			rtn = L" ";
	}
	return rtn;
	
}
*/
bool isblank(SIchar_t tt)
{
	return tt == L' ' || tt == L'\r' || tt == L'\n';
}

inline void token(char* ifilename, char* ofilename)
{
	wifstream wfin;
	wofstream wfout;

	//wfin.imbue(locale("C.UTF-8"));
//	wfin.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));

	wfin.open(ifilename);
	wfout.open(ofilename);

	//wfin.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>));
	//wfin.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));

//	ios_base::sync_with_stdio(false);
//	wcin.imbue(locale("C.UTF-8"));
//	setlocale(LC_ALL, "C.UTF-8");
//	wcout.imbue(locale("C.UTF-8"));

// 	const std::locale empty_locale = std::locale::empty();
//	typedef std::codecvt_utf8<wchar_t> converter_type;
//	const converter_type* converter = new converter_type;
//	const std::locale utf8_locale = std::locale(empty_locale, converter);
//	std::wifstream stream(L"test.txt");
//	wfin.imbue(utf8_locale);
//	std::wstring line;
//	std::getline(stream, line);
//	std::system("pause");

//	locale chs("chs");
//	wfin.imbue(chs);

	wstring xx;
	wstring temp;
	bool flag;
	int size;
	wchar_t ch;
	SIchar_t ch_pre=L'*';
	string stemp;
	while (wfin >> ch)
	{
	//	wcout << ch;
		//if (ch == L'&')
		//{
			//temp += transcode(wfin);
			//wcout << temp << endl;
		//}
		if (ch != L'<'&&ch != L'>')//&&!isblank(ch)) 
			temp += ch;//wfout << ch;
		else if (ch == L'<')
		{
			//(x&=((1<<8)-1))
			wfout << temp << endl;
			temp.clear();
			temp += ch;
		}
		else
		{
			temp += ch;
			if(temp.size()) wfout << temp << endl;
			temp.clear();
			
		}
	//	wcout << ch << endl;
	//	cout << temp.size();
	}
/*	
	while (wfin >> ch)
	{
		if(ch!=L'<'&&ch!=L'>') wfout << ch;
		else
		{
			wfout << endl << ch << endl;
		}
	}
*/
/*
	while (wfin >> temp)
	{
		wfout << temp << endl;
	}
*/
/*
	while (getline(wfin, temp))
	//while (wfin >> temp)
	{
		size = temp.size();
		preEndl = true;
		for (int i = 0; i != size; ++i)
		{
			if (temp[i] == L' '&&i != 0 && temp[i - 1] == L' ') continue;
			wfout << temp[i];
			if (temp[i] == L'>')
			{
				preEndl = true;
				wfout << endl;
			}
			if (i < size - 1 && temp[i + 1] == L'<')
			{
	
			}
		}
	}
	*/
	wfin.close();
	wfout.close();
}

inline void token2(char* ifilename, char* ofilename)
{
	ofstream fout;
	
	fout.open(ofilename);

	FILE* fin = fopen(ifilename, "r");

	wstring xx;
	string temp;
	bool flag = false;
	int size;
	char ch;
	SIchar_t ch_pre = L'*';
	string stemp;
	while (fscanf(fin,"%c", &ch) != EOF)
	{
		if ((ch == '\n' || ch == '\r') && flag)
			temp += ' ';
		else if (ch != '<'&&ch != '>') 
			temp += ch;
		else if (ch == '<')
		{
			flag = true;
			fout << temp << endl;
			temp.clear();
			temp += ch;
		}
		else /// ch=='>'
		{
			flag = false;
			temp += ch;
			if (temp.size()) fout << temp << endl;
			temp.clear();

		}
	}
	
	fclose(fin);
	fout.close();
}

wchar_t s[100086];

inline int getlen(wchar_t* s)
{
	int i = 0;
	for (; s[i] != L'\0'; ++i);
	return i;
}
int main()
{
	setlocale(LC_ALL, "zh_CN.GBK");

	token2("res.html", "res4.tok");
	return 0;
}