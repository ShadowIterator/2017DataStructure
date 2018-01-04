#ifndef PAGEINFO_H
#define PAGEINFO_H

#include"sistring.h"
#include"si_global.h"

namespace SI
{
	class PageInfo
	{
	public:
		int id;
		int nid;
	//	int ocr;
	//	SIString keyWord;
		SIString url;
		SIString genType;
		SIString spcType;
		SIString title;
		SIString contents;
		SIString author;
		SIString date;
		SIString pref;
		SIStringList wordList;
		
		PageInfo() {}

		PageInfo(int tid,
			int tnid,
			//const SIString& keyWord;
			const SIString& tgenType,
			const SIString& tspcType,
			const SIString& ttitle,
			const SIString& tcontents,
			const SIString& tauthor,
			const SIString& tdate,
			const SIString& tpref,
			SIStringList& twordList) :
			id(tid),
			nid(tnid),
			genType(tgenType),
			spcType(tspcType),
			title(ttitle),
			contents(tcontents),
			author(tauthor),
			date(tdate),
			pref(tpref),
			wordList(twordList)
		{

		}

		PageInfo(PageInfo& pinfo):
			id(pinfo.id),
			nid(pinfo.nid),
			genType(pinfo.genType),
			spcType(pinfo.spcType),
			title(pinfo.title),
			contents(pinfo.contents),
			author(pinfo.author),
			date(pinfo.date),
			pref(pinfo.pref),
			wordList(pinfo.wordList)
		{
			
		}
		void extractInfo(SIString& sistr);
		void set_nid(int tnid);
/*
		bool operator < (const PageInfo& tinfo);
		bool operator > (const PageInfo& tinfo);
		bool operator == (const PageInfo& tinfo);
*/
	};
}

#endif