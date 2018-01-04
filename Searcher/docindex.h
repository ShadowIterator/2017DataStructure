#ifndef DOCINDEX_H
#define DOCINDEX_H

/**
@brief DocIndex\n
@file docindex.h
@author ShadowIterator
@email ShadowIterator@hotmail.com
@version 0.1
@date 2017.12.24
*/

#include"si_global.h"
#include"linklist.h"
#include"sistring.h"
#include"pageinfo.h"
#include"indexlistnode.h"

namespace SI
{
	/*
	@brief 用于描述一条索引信息\n
	*/
	class DocIndex
	{
	public:
		typedef IndexListNode node;
		SIString* pword;	///<索引关键词
		linklist<node>* ppageList;	///<指向文档链表的指针
		DocIndex(const SIString& tword);
		DocIndex(const DocIndex& tindex);
		DocIndex();
		//it will do nothing
		/*
		@brief 析构函数\n
		@note 析构函数不会做任何操作，需要手动调用destroy()方法
		@see_also SI::DocIndex::destroy
		*/
		~DocIndex();	
		//call this method when U don't need the data any more
		void destroy();	///<释放空间
		void insertPage(const node& tpage);	///<向文档列表中插入节点并保持有序
		int hash(int P) const;	///<得到关键词的HASH值

		bool operator < (const DocIndex& tindex) const;
		bool operator > (const DocIndex& tindex) const;
		bool operator == (const DocIndex& tindex) const;
	};
}
#endif