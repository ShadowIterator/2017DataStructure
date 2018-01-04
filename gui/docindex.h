#ifndef DOCINDEX_H
#define DOCINDEX_H

#include"si_global.h"
#include"linklist.h"
#include"sistring.h"
#include"pageinfo.h"
#include"indexlistnode.h"

namespace SI
{
	class DocIndex
	{
	public:
		typedef IndexListNode node;
		SIString* pword;
		linklist<node>* ppageList;
		DocIndex(const SIString& tword);
		DocIndex(const DocIndex& tindex);
		DocIndex();
		//it will do nothing
		~DocIndex();
		//call this method when U don't need the data any more
		void destroy();
		void insertPage(const node& tpage);
		int hash(int P) const;

		bool operator < (const DocIndex& tindex) const;
		bool operator > (const DocIndex& tindex) const;
		bool operator == (const DocIndex& tindex) const;
	};
}
#endif