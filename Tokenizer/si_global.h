#ifndef SI_GLOBAL_H
#define SI_GLOBAL_H

/**
@brief 解析网页前的预处理\n
@file si_global.h
@author ShadowIterator
@email ShadowIterator@hotmail.com
@version 0.1
@date 2017.11.7
*/

#include<cstdio>
#include<string>
#include<string.h>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<set>
#include<map>
#include<list>
#include<vector>
#include<fstream>
#include<locale>
#include<codecvt>

namespace SI
{
	class SIString;
	class PageInfo;
	typedef char SIchar_t;
	typedef int SIsize_t;
	
	template<class T>
	T Max(const T& a, const T& b)
	{
		return a > b ? a : b;
	}

	template<class T>
	T Min(const T& a,const T& b)
	{
		return a < b ? a : b;
	}
}
#endif //SI_GLOBAL_H