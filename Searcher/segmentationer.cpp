#include"segmentationer.h"

namespace SI
{
	ACAuto Segmentationer::T;
	const int Segmentationer::MAX_LEN = 100005;
	const int Segmentationer::MAX_MATCH = 1000005;
	const SIsize_t Segmentationer::BUFF_SIZE = 1024;
	char* Segmentationer::buff = NULL;
	int* Segmentationer::f = NULL;
	int* Segmentationer::prev = NULL;
	int* Segmentationer::last = NULL;
	int* Segmentationer::next = NULL;
	int* Segmentationer::st = NULL;
	int Segmentationer::tot = 0;

	Segmentationer::Segmentationer()
	{

	}
	
	void Segmentationer::allocBuff(SIsize_t buffsize)
	{
		buff = _alloc(buff, buffsize);
		f = _alloc(f, MAX_LEN);
		prev = _alloc(prev, MAX_LEN);
		last = _alloc(last, MAX_LEN);
		next = _alloc(next, MAX_MATCH);
		st = _alloc(st, MAX_MATCH);
	}

	void Segmentationer::destroyBuff()
	{
		_destroy(buff);
		_destroy(f);
		_destroy(prev);
		_destroy(last);
		_destroy(next);
		_destroy(st);
	}
	
	void Segmentationer::addrange(int s, int e)
	{
		++tot;
		next[tot] = last[e];
		st[tot] = s;
		last[e] = tot;
	}

	void Segmentationer::loadDic(char* infile)
	{
		FILE* fin = fopen(infile, "r");
		SIString temp;
		while (fscanf(fin, "%s", buff) != EOF)
		{
			temp.fromCstr(buff);
			T.insertString(temp);
		}
		T.calcFail();
		fclose(fin);
	}
	
	SIStringList Segmentationer::_doSegmentation(SIString& s)
	{
		SIStringList rtn;
		_ACAuto_Node* p = T.root;
		_ACAuto_Node* np;
		_ACAuto_Node* nq;
		SIsize_t slen = s.getsize();
		SIchar_t ch;
		tot = 0;
		f[0] = 0;
		for (int i = slen * slen; i >= 0; --i) next[i] = 0;
		for (int i = 0; i <= slen; ++i) last[i] = 0;
		for (int i = 0; i < slen; ++i)
		{
			for (ch = s[i]; p != NULL && p->son.find(ch) == p->son.end(); p = p->fail);
			if (p == NULL) p = T.root;
			else p = p->son[ch];
			for (np = p; np != NULL; np = np->fail)
				if (np->endOfString)
					addrange(i - np->len + 2, i + 1);
		}

		for (int i = 1; i <= slen; ++i)
		{
			f[i] = f[i - 1] + 1;
			prev[i] = i - 1;
			for(int pp=last[i];pp;pp=next[pp])
				if (f[i] > f[st[pp] - 1] + 1)
					f[i] = f[prev[i] = st[pp] - 1] + 1;
		}
		for (int i = slen; i > 0; i = prev[i])
			rtn.push_back(s.substring(prev[i], i - prev[i]));
		return rtn;
	}

	SIStringList Segmentationer::doSegmentation(SIString& contents)
	{
		SIString temp;
		SIStringList res, rtn;
		int s = 0, e;
		SIsize_t clen = contents.getsize();
		int i;
		for (i = 0; i < clen&&SIString::isstopsym(contents[i]); ++i);
		for (i = 0; i < clen; ++i)
		{
			if (SIString::ischar(contents[i]))
			{
				res = Segmentationer::_doSegmentation(temp);
				for (int k = res.size() - 1; k >= 0; --k)
					if (!res[k].checkBlank()) rtn.push_back(res[k]);
				temp.clear();
				for (; i < clen && SIString::ischar(contents[i]); ++i)
					temp += contents[i];

				rtn.push_back(temp);
				temp.clear();
				--i;
				continue;
			}
			temp += contents[i];
			if (SIString::isstopsym(contents[i]))
				if (temp.getsize() > 0)
				{
					res = Segmentationer::_doSegmentation(temp);
					for (int k = res.size() - 1; k >= 0; --k)
						if (!res[k].checkBlank()) rtn.push_back(res[k]);
					temp.clear();
				}
			while (i < clen&&SIString::isstopsym(contents[i]))
				++i;
		}
		res = Segmentationer::_doSegmentation(temp);
		for (int k = res.size() - 1; k >= 0; --k)
			if (!res[k].checkBlank()) rtn.push_back(res[k]);
		
		return rtn;
	}
}