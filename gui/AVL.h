#ifndef AVL_H
#define AVL_H
#include "si_global.h"

namespace SI
{
	template<class T>
	class AVL_Node
	{
	public:
		T* pval;
		int cnt, h;
		AVL_Node* fath;
		AVL_Node* ls;
		AVL_Node* rs;

		AVL_Node(AVL_Node* pfath, AVL_Node* pls, AVL_Node* prs) :fath(pfath), ls(pls), rs(prs) //:fath(NULL), ls(NULL), rs(NULL)
		{
			pval = NULL;
			cnt = 0;
			h = 0;
		}

		AVL_Node(AVL_Node* pfath, AVL_Node* pls, AVL_Node* prs, T* tval, int tcnt, int th) :fath(pfath), ls(pls), rs(prs), pval(tval), cnt(tcnt), h(th) //:fath(NULL), ls(NULL), rs(NULL)
		{
		}

		AVL_Node(AVL_Node* pfath, AVL_Node* pls, AVL_Node* prs, const T& tval, int tcnt, int th) :fath(pfath), ls(pls), rs(prs), cnt(tcnt), h(th) //:fath(NULL), ls(NULL), rs(NULL)
		{
			pval = new T(tval);
		}

		AVL_Node() :fath(NULL), ls(NULL), rs(NULL)
		{
			pval = NULL;
			cnt = 0;
			h = 0;
		}

		~AVL_Node()
		{
			delete pval;
		}
		void _init(AVL_Node* pfath, AVL_Node* pls, AVL_Node* prs)
		{
			fath = pfath;
			ls = pls;
			rs = prs;
			cnt = h = 0;
			pval = NULL;
		}
	};

	template<class T>
	class AVL
	{
	public:
		AVL_Node<T>* root;
		AVL_Node<T>* PNULL;
		typedef AVL_Node<T> node;
		AVL() :root(NULL)
		{
			PNULL = new node(PNULL, PNULL, PNULL);
		}

		node* newNode(node* pfath, node* pls, node* prs, const T& tval, int tcnt, int th)
		{
			return new node(pfath, pls, prs, tval, tcnt, th);
		}

		void setNull(const T& tval)
		{
			*(PNULL->pval) = tval;
		}

		void update(node* pi)
		{
			if (pi == PNULL) return;
			pi->cnt = 1;
			pi->h = 1;
			if (pi->ls != PNULL)
			{
				pi->cnt += pi->ls->cnt;
				pi->h = Max(pi->h, pi->ls->h + 1);
			}
			if (pi->rs != PNULL)
			{
				pi->cnt += pi->rs->cnt;
				pi->h = Max(pi->h, pi->rs->h + 1);
			}
		}

		int bfactor(node* pi)
		{
			return pi->ls->h - pi->rs->h;
		}

		void zig(node* pi)
		{
			node* pfa = pi->fath;
			pfa->ls = pi->rs;
			if (pi->rs != PNULL) pi->rs->fath = pfa;
			if (pfa->fath->ls == pfa) pfa->fath->ls = pi;
			if (pfa->fath->rs == pfa) pfa->fath->rs = pi;
			pi->fath = pfa->fath;
			pi->rs = pfa;
			pfa->fath = pi;
			if (pfa == root) root = pi;
			update(pfa);
			update(pi);
		}

		void zag(node* pi)
		{
			node* pfa = pi->fath;
			pfa->rs = pi->ls;
			if (pi->ls != PNULL) pi->ls->fath = pfa;
			if (pfa->fath->ls == pfa) pfa->fath->ls = pi;
			if (pfa->fath->rs == pfa) pfa->fath->rs = pi;
			pi->fath = pfa->fath;
			pi->ls = pfa;
			pfa->fath = pi;
			if (pfa == root) root = pi;
			update(pfa);
			update(pi);
		}

		void lh(node* pi)
		{
			node* pls = pi->ls;
			node* plls = pls->ls;
			node* plrs = pls->rs;
			if (plls->h > plrs->h) zig(pls);
			else { zag(plrs); zig(plrs); }
		}

		void rh(node* pi)
		{
			node* prs = pi->rs;
			node* prls = prs->ls;
			node* prrs = prs->rs;
			if (prrs->h > prls->h) zag(prs);
			else { zig(prls); zag(prls); }
		}
		void maintain(node* pi)
		{
			int bf;
			node* pfa;
			while (pi != PNULL)
			{
				pfa = pi->fath;
				update(pi);
				bf = pi->ls->h - pi->rs->h;
				if (bf > 1) lh(pi);
				else if (bf < -1) rh(pi);
				pi = pfa;
			}
		}

		node* ins(const T& k)
		{
			if (root == NULL)
			{
				root = newNode(PNULL, PNULL, PNULL, k, 1, 1);
				return root;
			}
			node* pi = root;
			node* pp = root;
			while (pi != PNULL)
			{
				pp = pi;
				if (*(pi->pval) == k) return pi;
				if (*(pi->pval) < k) pi = pi->rs;
				else pi = pi->ls;
			}
			node* np = newNode(pp, PNULL, PNULL, k, 1, 1);
			if (*(pp->pval) < k) pp->rs = np;
			else pp->ls = np;
			maintain(pp);
			return np;
		}

		int del_dfs(node*& troot, const T& k)
		{
			node* pi = troot;
			node* pp;
			node* pfa;
			while (pi != PNULL)
			{
				if (*(pi->pval) == k) break;
				if (*(pi->pval) < k) pi = pi->rs;
				else pi = pi->ls;
			}
			if (pi == PNULL) return 0;
			pfa = pi->fath;
			if (pi->ls == PNULL)
			{
				if (troot == pi)
				{
					pi->rs->fath = pfa;
					troot = pi->rs;
				}
				else
				{
					pi->rs->fath = pfa;
					if (pfa->ls == pi) pi->fath->ls = pi->rs;
					else pfa->rs = pi->rs;
				}
				maintain(pfa);
				delete pi;
			}
			else if (pi->rs == PNULL)
			{
				if (troot == pi)
				{
					pi->ls->fath = pfa;
					troot = pi->ls;
				}
				else
				{
					pi->ls->fath = pfa;
					if (pfa->ls == pi) pfa->ls = pi->ls;
					else pfa->rs = pi->ls;
				}
				maintain(pfa);
				delete pi;
			}
			else
			{
				if (bfactor(pi) >= 0)
				{
					for (pp = pi->ls; pp->rs != PNULL; pp = pp->rs);
					(*pi->pval) = *(pp->pval);
					del_dfs(pi->ls, *(pp->pval));
				}
				else
				{
					for (pp = pi->rs; pp->ls != PNULL; pp = pp->ls);
					(*pi->pval) = *(pp->pval);
					del_dfs(pi->rs, *(pp->pval));
				}
			}
		}

		void del(const T& k)
		{
			del_dfs(root, k);
		}

		node* find(const T& tval)
		{
			if (root == NULL) return NULL;
			node* pi = root;
			while (pi != PNULL)
			{
				if (tval == *(pi->pval)) return pi;
				if (*(pi->pval) < tval) pi = pi->rs;
				else pi = pi->ls;
			}
			return NULL;
		}

		T& find_k_ref(int K)
		{
			node* pi = root;
			int lscnt;
			while (pi != PNULL)
			{
				if (K == (lscnt = pi->ls->cnt) + 1) return *(pi->pval);
				if (K <= lscnt) pi = pi->ls;
				else
				{
					K -= (lscnt + 1);
					pi = pi->rs;
				}
			}
			return *(PNULL->pval);
		}

		T find_k_copy(int K)
		{
			node* pi = root;
			int lscnt;
			while (pi != PNULL)
			{
				if (K == (lscnt = pi->ls->cnt) + 1) return *(pi->pval);
				if (K <= lscnt) pi = pi->ls;
				else
				{
					K -= (lscnt + 1);
					pi = pi->rs;
				}
			}
			return *(PNULL->pval);
		}

		T find_k_ptr(int K)
		{
			node* pi = root;
			int lscnt;
			while (pi != PNULL)
			{
				if (K == (lscnt = pi->ls->cnt) + 1) return pi;//*(pi->pval);
				if (K <= lscnt) pi = pi->ls;
				else
				{
					K -= (lscnt + 1);
					pi = pi->rs;
				}
			}
			return NULL;//*(PNULL->pval);
		}
	};
}

#endif