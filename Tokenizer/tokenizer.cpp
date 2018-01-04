#define _CRT_SECURE_NO_WARNINGS
#include"si_global.h"
#include<cstdio>

using namespace std;

using SI::SIString;
using SI::SIchar_t;
using SI::SIsize_t;

bool isblank(SIchar_t tt)
{
	return tt == L' ' || tt == L'\r' || tt == L'\n';
}

inline void token(char* ifilename, char* ofilename)
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
			temp += L'\r';
		}
		else 
		{
			flag = false;
			temp += L'\r';
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

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "zh_CN.GBK");

	token(argv[1], argv[2]);
	return 0;
}