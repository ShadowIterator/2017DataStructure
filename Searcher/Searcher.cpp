#include"si_global.h"
#include"AVL.h"
#include"linklist.h"
#include"sistring.h"
#include"pageinfo.h"
#include"docindex.h"
#include"indexlistnode.h"
#include"hash.h"
#include"query.h"
#include"interface.h"
#include"segmentationer.h"

//#define DOHASH

using SI::linklist;
using SI::SIchar_t;
using SI::SIsize_t;
using SI::SIString;
using SI::SIStringList;
using SI::Element;
using SI::ACAuto;
using SI::AVL;
using SI::AVL_Node;
using SI::DocIndex;
using SI::PageInfo;
using SI::IndexListNode;
using SI::Segmentationer;
using SI::HASH;
using SI::Query;
typedef std::map<SIString, SIString> mss;
typedef std::map<SIString, SIString>::iterator mssi;

using namespace std;

Query Q;

char cs[SI::DEFULT_BUFFER_SIZE];

int clk;

int main()
{
	SI::initDictionary();
	cout << "Currently running ";
#ifdef DOAVL
	cout << "AVL" << endl;
#endif
#ifdef DOHASH
	cout << "HASH" << endl;
#endif
#ifdef DOSPLAY
	cout << "SPLAY" << endl;
#endif
	clk = clock();
#ifdef DOAVL
	Q._init_AVL("info.csv");
#endif //DOAVL
#ifdef DOHASH
	Q._init_HASH("info.csv");
#endif //DOHASH
#ifdef DOSPLAY
	Q._init_SPLAY("info.csv");
#endif //DOSPLAY
	cout << "INIT TIME: " << clock() - clk << endl;
	FILE* fin = fopen("query.txt", "r");
	ofstream fout;
	fout.open("result.txt");
	SIStringList slist;
	SIStringList temp;
	SIStringList queryList;
	SIString str;
	int NN = 0;
	clk = clock();
	while (Query::readline(fin, cs))
	{
#ifndef SILENCE
		if (NN % 100 == 0)
			cout << "Dealing with the " << NN << "th to the " << NN + 100 - 1 << "th queries" << endl;
		++NN;
#endif // !SILENCE
		str.fromCstr(cs);
		slist = str.split(' ');
		queryList._clear();
		for (SIStringList::Iterator it = slist.begin(); it != slist.end(); ++it)
		{
			queryList.push_back(Segmentationer::doSegmentation(*it));
		}
#ifdef DOAVL
		Q.batquery_AVL(queryList, fout);
#endif	//DOAVL
#ifdef DOHASH
		Q.batquery_HASH(queryList, fout);
#endif	//DOHASH
#ifdef DOSPLAY
		Q.batquery_SPLAY(queryList, fout);
#endif //DOSPLAY
		fout << endl;
	}
	
	cout << "QUERY TIME: " << clock() - clk << endl;

	SI::destroyDictionary();

	return 0;
}