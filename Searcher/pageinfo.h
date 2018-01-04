#ifndef PAGEINFO_H
#define PAGEINFO_H

/**
@brief PageInfo\n
@file pageinfo.h
@author ShadowIterator
@email ShadowIterator@hotmail.com
@version 0.1
@date 2017.12.24
*/

#include"sistring.h"
#include"si_global.h"

namespace SI
{
	/*
	@brief 用于描述一个网页/文档的相关信息\n
	*/
	class PageInfo
	{
	public:
		int id;	///<网页序号
		int nid;	///<索引用的序号
		SIString url;	///<网址
		SIString genType;	///<发帖大类
		SIString spcType;	///<发帖小类
		SIString title;	///<标题
		SIString contents;	///<内容
		SIString author;	///<作者
		SIString date;	///<日期
		SIString pref;	///<发帖类型
		SIStringList wordList;	///<分词结果
		
		PageInfo() {}

		PageInfo(int tid,
			int tnid,
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
		void extractInfo(SIString& sistr);	///<从一个字符串中解析相应信息
		void set_nid(int tnid);	///<设置索引序号

	};
}

#endif