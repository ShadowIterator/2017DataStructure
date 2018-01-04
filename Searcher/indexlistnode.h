#ifndef INDEXLISTNODE_H
#define INDEXLISTNODE_H

/**
@brief IndexListNode\n
@file indexlistnode.h
@author ShadowIterator
@email ShadowIterator@hotmail.com
@version 0.1
@date 2017.12.24
*/

#include"si_global.h"

namespace SI
{
	/*
	@brief 用于文档链表中的节点\n
	*/
	class IndexListNode
	{
	public:
		PageInfo* ppage;	///<指向一个文档的指针(标识不同的文档)
		int ocr;	///<这个文档中特定关键字出现的次数
		IndexListNode(PageInfo* tpage, int tocr) :ppage(tpage), ocr(tocr)
		{

		}
		IndexListNode() :ppage(NULL), ocr(0)
		{

		}
	};
}

#endif