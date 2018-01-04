#ifndef SI_GLOBAL_H
#define SI_GLOBAL_H

/**
@brief 全局信息\n
@file si_global.h
@author ShadowIterator
@email ShadowIterator@hotmail.com
@version 0.1
@date 2017.11.10
*/

#define _CRT_SECURE_NO_WARNINGS
//#include "stdafx.h"
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
#include<queue>
#include<locale>
#include<codecvt>

namespace SI
{
	class SIString;	///<字符串类
	class Element;	///<html元素类
	class SelfClosedLabel;	
	class ACAuto;
	class PageInfo;
	class IndexListNode;
	class DocIndex;
	class Query;

	typedef wchar_t SIchar_t;
	typedef int SIsize_t;
	
	template<class T>
	inline void _exchange_xor(T& a, T& b)	///<交换两个数
	{
		a ^= b ^= a ^= b;
	}

	template<class T>
	inline T Max(const T& a, const T& b)	///<取最大
	{
		return a > b ? a : b;
	}

	template<class T>
	inline T Min(const T& a,const T& b)	///<取最小
	{
		return a < b ? a : b;
	}
}
#endif //SI_GLOBAL_H