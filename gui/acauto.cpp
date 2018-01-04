//#include"si_global.h"
#include "stdafx.h"
#include"acauto.h"

namespace SI
{
	using std::map;
	using std::queue;

	typedef map<SIchar_t, _ACAuto_Node*> mcp;

	queue<_ACAuto_Node*> ACAuto::q;
	
	_ACAuto_Node::_ACAuto_Node() :fail(NULL),len(0),endOfString(false)
	{
		son.clear();
	}

	ACAuto::ACAuto()
	{
		root = new node;
	//	root->len = 1;
	//	root->endOfString = true;
	}

	void ACAuto::insertString(const SIString& s)
	{
		nodeptr p = root;
		SIsize_t slen = s.getsize();
		for (int i = 0; i < slen; ++i)
		{
			if (p->son[s[i]] == NULL)
				p->son[s[i]] = new node;
			p = p->son[s[i]];
		}
		p->len = slen;
		p->endOfString = true;
	}

	void ACAuto::calcFail()
	{
		while (!q.empty()) q.pop();
		root->fail = NULL;
		q.push(root);
		nodeptr p, np;
		SIchar_t ch;
		while (!q.empty())
		{
			p = q.front();
			q.pop();
			for (mcp::iterator it = p->son.begin(); it != p->son.end(); ++it)
			{
				ch = it->first;
				for(np=p->fail;np!=NULL;np=np->fail)
					if (np->son.find(ch) != np->son.end())
					{
						it->second->fail = np->son[ch];
						break;
					}
				if (np == NULL) it->second->fail = root;
				q.push(it->second);
			}
		}
		//root->fail = root;
	}
}