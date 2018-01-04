#ifndef QUERY_H
#define QUERY_H

#include"si_global.h"
#include"AVL.h"
#include"linklist.h"
#include"sistring.h"
#include"pageinfo.h"
#include"docindex.h"
#include"indexlistnode.h"
#include"hash.h"

namespace SI
{
	const int MAXPAGE = 4005;
	const int DEFULT_BUFFER_SIZE = 100086;

	class Query
	{
	public:
		int N = 0;
		static char cs[DEFULT_BUFFER_SIZE];	///<ÊäÈë»º³åÇø
		static int cnt[MAXPAGE + 5];
		static int rank_id[MAXPAGE + 5];
		static int sigmac2[MAXPAGE + 5];
		static int T[MAXPAGE + 5];
		static double w[MAXPAGE + 5];
		PageInfo pages[MAXPAGE + 5];

		AVL<DocIndex> AVL;
		HASH<DocIndex> H;//(8388593, 65537);

		Query();
		static bool cmp_sistring(const SIString& s1, const SIString& s2);
		static  bool cmp_rank_id(int a, int b);
		void _init();
		void _init_AVL(char* filename);
		void _init_HASH(char* filename);
		linklist<IndexListNode>* query_AVL(const SIString& word);
		linklist<IndexListNode>* query_HASH(const SIString& word);
		void batquery_AVL(SIStringList& slist, linklist<IndexListNode>& res);
		void batquery_HASH(SIStringList& slist, linklist<IndexListNode>& res);
		static bool readline(FILE* infile, char* s);
		PageInfo* getPage(int id);
	};
}

#endif // ! QUERY_H
