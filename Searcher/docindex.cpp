#include"si_global.h"
#include"docindex.h"

namespace SI
{
	DocIndex::DocIndex() :pword(NULL), ppageList(NULL)
	{

	}
	DocIndex::DocIndex(const SIString& tword)
	{
		pword = new SIString(tword);
		ppageList = new linklist<node>;
	}
	DocIndex::DocIndex(const DocIndex& tindex):pword(tindex.pword),ppageList(tindex.ppageList)
	{
		
	}
	DocIndex::~DocIndex()
	{
		
	}
	void DocIndex::destroy()
	{
		delete pword;
		delete ppageList;
		pword = NULL;
		ppageList = NULL;
	}
	void DocIndex::insertPage(const node& tnode)
	{
		linklist<node>::Iterator it; 
		for (it = ppageList->begin(); it != ppageList->end(); ++it)
			if ((*it).ocr <= tnode.ocr) break;
		ppageList->insert(--it, tnode);
	}
	bool DocIndex::operator < (const DocIndex& tnode) const
	{
		return (*pword) < (*(tnode.pword));
	}
	bool DocIndex::operator > (const DocIndex& tnode) const
	{
		return (*pword) > (*(tnode.pword));
	}
	bool DocIndex::operator == (const DocIndex& tnode) const 
	{
		return (*pword) == (*(tnode.pword));
	}
	int DocIndex::hash(int P) const
	{
		return pword->hash(P);
	}
}