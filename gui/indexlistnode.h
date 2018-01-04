#ifndef INDEXLISTNODE_H
#define INDEXLISTNODE_H

#include"si_global.h"

namespace SI
{
	class IndexListNode
	{
	public:
		PageInfo* ppage;
		int ocr;
		IndexListNode(PageInfo* tpage, int tocr) :ppage(tpage), ocr(tocr)
		{

		}
		IndexListNode() :ppage(NULL), ocr(0)
		{

		}
	};
}

#endif