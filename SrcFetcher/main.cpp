#include"srcfetcher.h"

int main(int argc, char* argv[])
{
	//char* inpfile = "test.html";
	//char* inpurl = "http://bbs.cehome.com/thread-614565-1-1.html";
	char *inpurl = argv[1];
	FILE* file = fopen(argv[2], "w");
	TCHAR* url = new TCHAR[MAXSIZE];
	//FILE* file = fopen(inpfile, "w");
#ifdef UNICODE
	MultiByteToWideChar(CP_ACP, 0, inpurl, -1, url, 100);
#else 
	strcpy(url, argv[1]);
#endif
	fetchHTML(url,file);
	return 0;
}