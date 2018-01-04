#ifndef HASH_H
#define HASH_H

/**
@brief HASH\n
@file hash.h
@author ShadowIterator
@email ShadowIterator@hotmail.com
@version 0.1
@date 2017.12.24
*/

#include"si_global.h"
#include"linklist.h"

namespace SI
{
	const int MAXP = 1 << 22;
	const int DEFAULTP = 4194301;
	const int DEFAULTSIGMA = 65537;

	/*
	@brief 哈希表\n
	@note 使用BKDR哈希
	*/
	template<typename T>
	class HASH
	{
	public:
		int P;	///<HASH的模数
		int sigma;	///<字符集大小
		linklist<T> data[MAXP];	///<链表法解决冲突
		
		HASH() :P(DEFAULTP),sigma(DEFAULTSIGMA) {}
		HASH(int tP,int tsigma) :P(tP),sigma(tsigma) {}
		HASH(int tsigma) :P(DEFAULTSIGMA), sigma(tsigma) {}

		T* insert(const T& tdata)	///<向哈希表中插入元素
		{
			int id = tdata.hash(P);
			linklist<T>* ptr = &data[id]; 
			linklist<T>::Iterator it;
			for (it = ptr->begin(); it != ptr->end(); ++it)
				if ((*it) == tdata) return &(*it);
			ptr->push_back(tdata);
			it = ptr->end();
			return &(*(--it));
		}

		T* find(const T& tdata)	///<在哈希表中查找元素
		{
			int id = tdata.hash(P);
			linklist<T>* ptr = &data[id];
			linklist<T>::Iterator it;
			for (it = ptr->begin(); it != ptr->end(); ++it)
				if ((*it) == tdata) return &(*it);
			return NULL;
		}

	};
}

#endif // !HASH_H
