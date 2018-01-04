#ifndef QUERY_H
#define QUERY_H

/**
@brief Query\n
@file query.h
@author ShadowIterator
@email ShadowIterator@hotmail.com
@version 0.1
@date 2017.12.24
*/

#include"si_global.h"
#include"AVL.h"
#include"linklist.h"
#include"sistring.h"
#include"pageinfo.h"
#include"docindex.h"
#include"indexlistnode.h"
#include"hash.h"
#include"splay.h"

namespace SI
{
	const int MAXPAGE = 4005;
	const int DEFULT_BUFFER_SIZE = 100086;

	/*
	@brief 询问类\n
	@note 可以使用AVL,Splay和HASH来索引文档链表和进行询问,需要定义相应的宏(DOAVL/DOSPLAY/DOHASH)来说明采用的数据结构\n
	*/
	class Query
	{
	public:
		int N = 0;	///<分配索引序号
		static char cs[DEFULT_BUFFER_SIZE];	///<输入缓冲区
		static int cnt[MAXPAGE + 5];
		static int rank_id[MAXPAGE + 5];
		static int sigmac2[MAXPAGE + 5];
		static int T[MAXPAGE + 5];
		static double w[MAXPAGE + 5];
		PageInfo pages[MAXPAGE + 5];	///<储存所有页面
#ifdef DOAVL
		AVL<DocIndex> AVL;	///< AVL索引
#endif //DOAVL
#ifdef DOHASH
		HASH<DocIndex> H;	///<HASH索引
#endif // DOHASH
#ifdef DOSPLAY
		Splay<DocIndex> SP;	///<Splay索引
#endif // DOSPLAY

		Query();
		static bool cmp_sistring(const SIString& s1, const SIString& s2);
		static  bool cmp_rank_id(int a, int b);
		static bool readline(FILE* infile, char* s);

		void _init();	///<初始化函数v
#ifdef DOAVL
		/*
		@brief 初始化AVL索引\n
		@param [in] filename 输入文件名\n
		*/
		void _init_AVL(char* filename);	
		/*
		@brief 单次询问\n
		@param [in] word 查询关键字
		@retval 包含关键词的文档链表(有序)
		*/
		linklist<IndexListNode>* query_AVL(const SIString& word);
		/*
		@brief 批量询问\n
		@param [in] slist 查询关键字列表
		@retval 包含关键词的文档链表(有序)
		*/
		void batquery_AVL(SIStringList& slist, std::ofstream& fout);
#endif // DOAVL

#ifdef DOHASH
		void _init_HASH(char* filename);
		linklist<IndexListNode>* query_HASH(const SIString& word);
		void batquery_HASH(SIStringList& slist, std::ofstream& fout);
#endif // DOHASH

#ifdef DOSPLAY
		void _init_SPLAY(char* filename);
		linklist<IndexListNode>* query_SPLAY(const SIString& word);
		void batquery_SPLAY(SIStringList& slist, std::ofstream& fout);
#endif // DOHASH
	
	};
}

#endif // ! QUERY_H
