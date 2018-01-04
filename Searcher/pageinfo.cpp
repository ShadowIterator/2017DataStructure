#include"si_global.h"
#include"pageinfo.h"

namespace SI
{
	void PageInfo::extractInfo(SIString& sistr)
	{
//		if (sistr.getsize() <= 0) return;
		SIStringList slist = sistr.split(',');
//		if (slist.size() <= 1 || slist.size() > 10) return;
//		if (slist.size() != 10) return;
		id = slist[0].toNumber();
		url = slist[1];
		genType = slist[2];
		spcType = slist[3];
		title = slist[4];
		contents = slist[5];
		author = slist[6];
		date = slist[7];
		pref = slist[8];
		wordList = slist[9].split(' ');
	/*
		std::cout << "id: " << id << std::endl
			<<"url: "<< url << std::endl
			<<"genType: "<< genType << std::endl
			<<"spcType: "<< spcType << std::endl
			<<"title: "<< title << std::endl
			<<"contents: "<< contents << std::endl
			<< "author: "<< author << std::endl
			<<"date: "<< date << std::endl
			<<"pref: "<< pref << std::endl << std::endl;
		
		std::cout << "words: ";
		for (int i = 0; i < wordList.size(); ++i)
			std::cout << wordList[i] << " ";
		std::cout << std::endl;
		*/
	}
	void PageInfo::set_nid(int tnid)
	{
		nid = tnid;
	}
}