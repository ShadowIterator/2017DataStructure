#include"selfclosedlabelchecker.h"
#include<fstream>

namespace SI
{
	SIStringList SelfClosedLabelChecker::labellist;
	char* SelfClosedLabelChecker::buff = NULL;
	const SIsize_t SelfClosedLabelChecker::BUFF_SIZE = 1024;
	void SelfClosedLabelChecker::allocBuff(SIsize_t buffsize)
	{
		if (buff != NULL)
			delete[] buff;
		buff = new char[buffsize];
	}
	void SelfClosedLabelChecker::destroyBuff()
	{
		if (buff != NULL)
			delete[] buff;
		buff = NULL;
	}
	void SelfClosedLabelChecker::init(char* infile)
	{
		FILE* fin = fopen(infile, "r");
		while(fscanf(fin,"%s",buff)!=EOF)
			labellist.push_back(SIString(buff));
	}
	
	bool SelfClosedLabelChecker::check(const SIString& str)
	{
		for (SIStringList::Iterator it = labellist.begin(); it != labellist.end(); ++it)
			if ((*it) == str) return true;
		return false;
	}
}