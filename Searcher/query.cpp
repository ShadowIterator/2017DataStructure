#include"query.h"

namespace SI
{
	using std::cout;
	using std::endl;

	char Query::cs[DEFULT_BUFFER_SIZE];
	int Query::cnt[MAXPAGE + 5];
	int Query::rank_id[MAXPAGE + 5];
	int Query::sigmac2[MAXPAGE + 5];
	int Query::T[MAXPAGE + 5];
	double Query::w[MAXPAGE + 5];

	const double EPS = 1e-8;
	const double INF = 1e100;

	inline int DBcmp(double a, double b)
	{
		if (a - b > EPS) return 1;
		if (b - a > EPS) return -1;
		return 0;
	}
	Query::Query() 
#ifdef DOHASH
		:H(65537)
#endif // DOHASH
	{
		_init();
	}

	bool Query::cmp_sistring(const SIString& s1, const SIString& s2)
	{
		return s1 < s2;
	}

	bool Query::cmp_rank_id(int a, int b)
	{
		return DBcmp(w[a], w[b]) < 0;
	}

	void Query::_init()
	{
		N = 0;
		for (int i = 0; i <= MAXPAGE; ++i) rank_id[i] = i;
	}

#ifdef DOAVL
	void Query::_init_AVL(char* filename)
	{
		FILE* fin = fopen(filename, "r");
		DocIndex* pindex;
		SIString sistr;
		SIStringList* pwordList;
		AVL_Node<DocIndex>* pavlNode;
		int wls;
		int ocr;
		readline(fin, cs);
		while (readline(fin, cs))
		{
			sistr.fromCstr(cs);
			pages[++N].extractInfo(sistr);
			pages[N].set_nid(N);
			pwordList = &(pages[N].wordList);
			wls = pwordList->size();
			pwordList->sort(cmp_sistring);
			for (int i = 0; i < wls; ++i)
			{
				ocr = 0;
				while (i < wls - 1 && (*pwordList)[i] == (*pwordList)[i + 1]) ++i, ++ocr;
				++ocr;
				pindex = new DocIndex((*pwordList)[i]);
				pavlNode = AVL.ins(*pindex);
				pavlNode->pval->insertPage(IndexListNode(&pages[N], ocr));
				delete pindex;
			}
		}
	//	fclose(fin);
	}

	linklist<IndexListNode>* Query::query_AVL(const SIString& word)
	{
		DocIndex* pindex = new DocIndex(word);
		AVL_Node<DocIndex>* pavlNode = AVL.find(*pindex);
		if (pavlNode != NULL)
			return pavlNode->pval->ppageList;
		return NULL;
	}

	void Query::batquery_AVL(SIStringList& slist, std::ofstream& fout)
	{
		memset(cnt, 0, sizeof(cnt));
		memset(T, 0, sizeof(T));
		memset(sigmac2, 0, sizeof(sigmac2));
		linklist<IndexListNode>* pres;
		int id, ocr;
		for (SIStringList::Iterator it = slist.begin(); it != slist.end(); ++it)
		{
			if ((pres = query_AVL(*it)) != NULL)
				for (linklist<IndexListNode>::Iterator it = pres->begin(); it != pres->end(); ++it)
				{
					cnt[(id = (*it).ppage->nid)] += (ocr = (*it).ocr);
					++T[id];
					sigmac2[id] += ocr*ocr;
				}
		}
		for (int i = 0; i < MAXPAGE; ++i)
		{
			if (cnt[i])
			{
				ocr = cnt[i] * cnt[i] * cnt[i];
				w[i] = (double)((long long)sigmac2[i] - (long long)T[i] * ocr) / ocr;
			}
			else w[i] = INF;
		}
		std::sort(rank_id, rank_id + MAXPAGE, cmp_rank_id);
		for (int i = 0; i < MAXPAGE && cnt[id = rank_id[i]] > 0; ++i)
		{
			fout << "(" << pages[id].id << "," << cnt[id] << ") ";
		}
}

#endif //DOAVL

	
#ifdef DOHASH

	void Query::_init_HASH(char* filename)
	{
		FILE* fin = fopen(filename, "r");
		DocIndex* pindex;
		SIString sistr;
		SIStringList* pwordList;
		DocIndex* phashindex;
		int wls;
		int ocr;
		readline(fin, cs);
		while (readline(fin, cs))
		{
			sistr.fromCstr(cs);
			pages[++N].extractInfo(sistr);
			pages[N].set_nid(N);
			pwordList = &(pages[N].wordList);
			wls = pwordList->size();
			pwordList->sort(cmp_sistring);
			for (int i = 0; i < wls; ++i)
			{
				ocr = 0;
				while (i < wls - 1 && (*pwordList)[i] == (*pwordList)[i + 1]) ++i, ++ocr;
				++ocr;
				pindex = new DocIndex((*pwordList)[i]);
				phashindex = H.insert(*pindex);
				phashindex->insertPage(IndexListNode(&pages[N], ocr));
				delete pindex;
			}
		}
		fclose(fin);
	}

	linklist<IndexListNode>* Query::query_HASH(const SIString& word)
	{
		DocIndex* pindex = new DocIndex(word);
		DocIndex* phashIndex = H.find(*pindex);
		if (phashIndex != NULL)
			return phashIndex->ppageList;
		return NULL;
	}

	void Query::batquery_HASH(SIStringList& slist, std::ofstream& fout)
	{
		memset(cnt, 0, sizeof(cnt));
		memset(T, 0, sizeof(T));
		memset(sigmac2, 0, sizeof(sigmac2));
		linklist<IndexListNode>* pres;
		int id, ocr;
		for (SIStringList::Iterator it = slist.begin(); it != slist.end(); ++it)
		{
			if ((pres = query_HASH(*it)) != NULL)
				for (linklist<IndexListNode>::Iterator it = pres->begin(); it != pres->end(); ++it)
				{
					cnt[(id = (*it).ppage->nid)] += (ocr = (*it).ocr);
					++T[id];
					sigmac2[id] += ocr*ocr;
				}
		}
		for (int i = 0; i < MAXPAGE; ++i)
		{
			if (cnt[i])
			{
				ocr = cnt[i] * cnt[i] * cnt[i];
				w[i] = (double)((long long)sigmac2[i] - (long long)T[i] * ocr) / ocr;
			}
			else w[i] = INF;
		}
		std::sort(rank_id, rank_id + MAXPAGE, cmp_rank_id);
		for (int i = 0; i < MAXPAGE && cnt[id = rank_id[i]] > 0; ++i)
		{
			fout << "(" << pages[id].id << "," << cnt[id] << ") ";
		}
	}


#endif // DOHASH



#ifdef DOSPLAY
	void Query::_init_SPLAY(char* filename)
	{
		FILE* fin = fopen(filename, "r");
		DocIndex* pindex;
		SIString sistr;
		SIStringList* pwordList;
		SplayNode<DocIndex>* psplayNode;
		int wls;
		int ocr;
		readline(fin, cs);
		while (readline(fin, cs))
		{
			sistr.fromCstr(cs);
			pages[++N].extractInfo(sistr);
			pages[N].set_nid(N);
			pwordList = &(pages[N].wordList);
			wls = pwordList->size();
			pwordList->sort(cmp_sistring);
			for (int i = 0; i < wls; ++i)
			{
				ocr = 0;
				while (i < wls - 1 && (*pwordList)[i] == (*pwordList)[i + 1]) ++i, ++ocr;
				++ocr;
				pindex = new DocIndex((*pwordList)[i]);
				psplayNode = SP.ins(*pindex);
				psplayNode->pval->insertPage(IndexListNode(&pages[N], ocr));
				delete pindex;
			}
		}
		fclose(fin);
	}

	linklist<IndexListNode>* Query::query_SPLAY(const SIString& word)
	{
		DocIndex* pindex = new DocIndex(word);
		SplayNode<DocIndex>* psplayNode = SP.find(*pindex);
		if (psplayNode != NULL)
			return psplayNode->pval->ppageList;
		return NULL;
	}

	void Query::batquery_SPLAY(SIStringList& slist, std::ofstream& fout)
	{
		memset(cnt, 0, sizeof(cnt));
		memset(T, 0, sizeof(T));
		memset(sigmac2, 0, sizeof(sigmac2));
		linklist<IndexListNode>* pres;
		int id, ocr;
		for (SIStringList::Iterator it = slist.begin(); it != slist.end(); ++it)
		{
			if ((pres = query_SPLAY(*it)) != NULL)
				for (linklist<IndexListNode>::Iterator it = pres->begin(); it != pres->end(); ++it)
				{
					cnt[(id = (*it).ppage->nid)] += (ocr = (*it).ocr);
					++T[id];
					sigmac2[id] += ocr*ocr;
				}
		}
		for (int i = 0; i < MAXPAGE; ++i)
		{
			if (cnt[i])
			{
				ocr = cnt[i] * cnt[i] * cnt[i];
				w[i] = (double)((long long)sigmac2[i] - (long long)T[i] * ocr) / ocr;
			}
			else w[i] = INF;
		}
		std::sort(rank_id, rank_id + MAXPAGE, cmp_rank_id);
		for (int i = 0; i < MAXPAGE && cnt[id = rank_id[i]] > 0; ++i)
		{
			fout << "(" << pages[id].id << "," << cnt[id] << ") ";
		}
	}


#endif //DOSPLAY

	bool Query::readline(FILE* infile, char* s)
	{
		char t;
		int len = 0;
		for (t = getc(infile); SIString::isenter(t); t = getc(infile));
		while (SIString::isblank(t)) t = getc(infile);
		if (t == EOF) return false;
		for (; !(SIString::isenter(t)) && t != EOF; t = getc(infile)) s[len++] = t;
		s[len++] = '\0';
		if (t == EOF) return false;
		return true;
	}
}