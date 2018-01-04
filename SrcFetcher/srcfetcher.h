#ifndef SRCFETCHER_H
#define SRCFETCHER_H


//@from ycdfwzy

/**
@brief 抓取网页\n
@file srcfetcher.h
@author ShadowIterator
@email ShadowIterator@hotmail.com
@version 0.1
@date 2017.11.7
*/


#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <cstring>
#include <windows.h>
#include <wininet.h>
#include <locale.h>  

#define MAXSIZE 1024
#pragma comment(lib, "Wininet.lib") 


void fetchHTML(TCHAR* url,FILE* tarFile);
void urlopen(TCHAR* url, FILE* tarFile);

#endif //SRCFETCHER_H