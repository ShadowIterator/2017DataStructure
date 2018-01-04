

#define DOHASH

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
#ifdef DOAVL
	cout << "AVL" << endl;
#endif
#ifdef DOHASH
	cout << "HASH" << endl;
#endif
	clk = clock();
#ifdef DOAVL
	Q._init_AVL("result.csv");
#endif
#ifdef DOHASH
	Q._init_HASH("result.csv");
#endif
	cout << "INIT TIME: " << clock() - clk << endl;
	FILE* fin = fopen("query.txt", "r");
	ofstream fout;
	fout.open("result.txt");
	SIStringList slist;
	SIStringList temp;
	SIStringList queryList;
	SIString str;

	clk = clock();
	while (Query::readline(fin, cs))
	{
		str.fromCstr(cs);
		slist = str.split(' ');
		queryList._clear();
		for (SIStringList::Iterator it = slist.begin(); it != slist.end(); ++it)
		{
			queryList.push_back(Segmentationer::doSegmentation(*it));
		}
#ifdef DOAVL
		Q.batquery_AVL(slist, fout);
#endif
#ifdef DOHASH
		Q.batquery_HASH(queryList, fout);
#endif
		fout << endl;
	}
	
	cout << "QUERY TIME: " << clock() - clk << endl;

	SI::destroyDictionary();

	return 0;
}