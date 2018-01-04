#ifndef SPLAY_H
#define SPLAY_H
/**
@brief Splay\n
@file splay.h
@author ShadowIterator
@email ShadowIterator@hotmail.com
@version 0.1
@date 2017.12.24
*/

#include"si_global.h"

namespace SI
{
	/*
	@brief Splay节点\n
	*/
	template<class T>
	class SplayNode
	{
	public:
		SplayNode* ls;	///<左儿子指针
		SplayNode* rs;	///<右儿子指针
		SplayNode* fath;///<父亲指针
		int cnt;	///<子树元素个数
		T* pval;	///<数据指针
		void clear()
		{
			ls = rs = fath = cnt = 0;
			pval = NULL;
		}

		SplayNode() :ls(NULL), rs(NULL), fath(NULL), cnt(0), pval(NULL) {}
		SplayNode(SplayNode* tls, SplayNode* trs, SplayNode* tfath, int tcnt, const T& tval) :
			ls(tls), rs(trs), fath(tfath), cnt(tcnt)
		{
			pval = new T(tval);
		}
		SplayNode(SplayNode* tls, SplayNode* trs, SplayNode* tfath, int tcnt) :
			ls(tls), rs(trs), fath(tfath), cnt(tcnt)
		{
		}


	};

	template<class T>
	class Splay
	{
	public:
		typedef SplayNode<T> node;
		node* root;	///<根节点指针
		node* PNULL;///<"空节点"指针
	public:
		Splay() :root(NULL)
		{
			PNULL = new node(PNULL, PNULL, PNULL, 0);
		}
		void update(node* pi)	///<更新节点信息
		{
			pi->cnt = pi->ls->cnt + pi->rs->cnt + 1;
		}

		void zig(node* pi)	///<向右旋转
		{
			node* pfa = pi->fath;
			if (pfa == PNULL) return;
			pfa->ls = pi->rs;
			if (pi->rs != PNULL) pi->rs->fath = pfa;
			pi->fath = pfa->fath;
			if (pfa->fath->ls == pfa) pfa->fath->ls = pi;
			if (pfa->fath->rs == pfa) pfa->fath->rs = pi;
			pi->rs = pfa;
			pfa->fath = pi;
			update(pfa);
			update(pi);
		}

		void zag(node* pi)	///<向左旋转
		{
			node* pfa = pi->fath;
			if (pfa == PNULL) return;
			pfa->rs = pi->ls;
			if (pi->ls != PNULL) pi->ls->fath = pfa;
			pi->fath = pfa->fath;
			if (pfa->fath->ls == pfa) pfa->fath->ls = pi;
			if (pfa->fath->rs == pfa) pfa->fath->rs = pi;
			pi->ls = pfa;
			pfa->fath = pi;
			update(pfa);
			update(pi);
		}
		/*
		@brief 伸展(Splay)操作
		@note 这个操作的效果是把一个节点旋转到根
		*/
		void splay(node* pi)	
		{
			node *pfa = pi->fath;
			node*pgp = pfa->fath;
			while (pgp != PNULL && pfa != PNULL)
			{
			if (pfa == pgp->ls)
				if (pi == pfa->ls) zig(pfa), zig(pi);
				else zag(pi), zig(pi);
			else
				if (pi == pfa->rs) zag(pfa), zag(pi);
				else zig(pi), zag(pi);
				pfa = pi->fath;
				pgp = pfa->fath;
			}
			if (pfa)
				if (pi == pfa->ls) zig(pi);
				else zag(pi);
				root = pi;
		}

		node* find(const T& tval)	///<查找节点
		{
			if (root == NULL) return NULL;
			node* pi = root;
			while (pi != PNULL)
			{
				if (tval == *(pi->pval))
				{
					splay(pi);
					return pi;
				}
				if (*(pi->pval) < tval) pi = pi->rs;
				else pi = pi->ls;
			}
			return NULL;
		}

		node* ins(const T& k)	///<插入节点
		{
			if (root == NULL)
			{
				root = new node(PNULL, PNULL, PNULL, 1, k);
				return root;
			}
			node* pi = root;
			node* pp = pi;
			while (pi != PNULL)
			{
				pp = pi;
				if (*(pi->pval) == k)
				{
					splay(pi);
					return pi;
				}
				if (*(pi->pval) < k) pi = pi->rs;
				else pi = pi->ls;
			}
			node* np;
			if (*(pp->pval) < k)
				np = pp->rs = new node(PNULL, PNULL, pp, 1, k);
			else
				np = pp->ls = new node(PNULL, PNULL, pp, 1, k);
			update(pp);
			splay(np);
			return np;
		}

		void del(const T& k)	///<删除节点
		{
			node* pi = root;
			node* pp = pi;
			node* pil;
			node* pir;
			while (pi != PNULL)
			{
				if (*(pi->pval) == k) break;
				if (*(pi->pval) < k) pi = pi->rs;
				else pi = pi->ls;
			}
			if (pi == PNULL) return;
			splay(pi);
			(pil = pi->ls)->fath = PNULL;
			(pir = pi->rs)->fath = PNULL;
			delete pi;
			if (pil == PNULL)root = pir;
			else if (pir == PNULL) root = pil;
			else
			{
				for (pp = pil; pp->rs != PNULL; pp = pp->rs);
				splay(pp);
				pp->rs = pir;
				pir->fath = pp;
				update(pp);
			}
		}

		T* find_K(int K)	///<找到Splay中排名第K小的节点
		{
			node* pi = root;
			while (pi != PNULL)
			{
				if (K == pi->ls->cnt + 1)
				{
					splay(pi);
					return (pi->pval);
				}
				if (K <= pi->ls->cnt) pi = pi->ls;
				else
				{
					K -= (pi->ls->cnt + 1);
					pi = pi->rs;
				}
			}
			return NULL;
		}
	};

}

#endif // !SPLAY_H
