#ifndef LINKLIST_H
#define LINKLIST_H

/**
@brief 链表模板\n
@file linklist.h
@author ShadowIterator
@email ShadowIterator@hotmail.com
@version 0.1
@date 2017.11.12
*/

#include"si_global.h"

namespace SI {

	/**
	@brief 链表节点模板类\n
	*/
	template<class T>
	class linklist_node
	{
		template<typename T>
		friend std::ostream& operator << (std::ostream& fout, const linklist_node<T>& tnode);

	public:
		linklist_node<T>* prev;	///<前一个节点
		linklist_node<T>* next;	///<后一个节点
		T* pdata;	///<指向存储内容的指针

	public:
		linklist_node(linklist_node<T>* tprev, linklist_node<T>* tnext, const T& tdata);
		linklist_node(linklist_node<T>* tprev, linklist_node<T>* tnext);
		linklist_node(const T& tdata);
		linklist_node();
		virtual ~linklist_node();
		void print();
		bool read();
	};

	template<typename T>
	std::ostream& operator << (std::ostream& fout, const linklist_node<T>& tnode)
	{
		fout << *(tnode.pdata);
		return fout;
	}

	/**
	@brief 链表模板类\n
	*/
	template<class T>
	class linklist
	{
		template<typename T>
		friend std::ostream& operator << (std::ostream& fout, const linklist<T>& tlist);

	private:
		linklist_node<T>* nowp;	///<指向最后一次下标访问的节点的指针，用于加速连续下标访问
		linklist_node<T>* defaultp;
		SIsize_t nowid;	///<最后一次访问的下标
		SIsize_t length; ///<链表长度
	public:
		class Iterator;	///<链表迭代器
		linklist_node<T>* head;	///<头指针
		linklist_node<T>* tail;	///<尾指针
	public:
		linklist();
		linklist(linklist& tlist)	///<拷贝构造函数
		{
			head = new linklist_node<T>();
			tail = new linklist_node<T>();
			defaultp = new linklist_node<T>();
			head->next = tail;
			tail->prev = head;
			nowp = head;
			nowid = -1;
			length = 0;

			int tsize = tlist.size();
			append(tsize);
			for (int i = 0; i < tsize; ++i)
				(*this)[i]=(tlist[i]);
		}
		/**
		@brief 释放链表\n
		@note 链表的内存会被释放
		*/
		void destroy()	
		{
			for (linklist_node<T>* p = head->next; p != tail; p = p->next)
			delete p->prev;
			delete tail;
			delete defaultp;
			head = tail = defaultp = NULL;
		}
		virtual ~linklist();
		/**
		@brief 清空链表\n
		@note 链表的内存不会被释放
		*/
		void _clear();	
		void _resetnow();	///<把nowp指针置为头节点
		/**
		@brief 移动nowp指针\n
		@param[in] p 移动的"下标"
		@retval true 移动成功
		@retval false 移动失败(越界访问)
		*/
		bool _movenow(SIsize_t p);	
		/**
		@brief 判断链表是否为空\n
		@retval true 链表为空
		@retval false 链表不为空
		*/
		bool empty()
		{
			return head->next == tail;
		}
		/**
		@brief 插入一个数据\n
		@param[in] p 待插入位置的前一个指针
		@param[in] tdata 待插入的数据
		@retval 指向插入节点的迭代器
		*/
		Iterator insert(linklist_node<T> *p, const T& tdata)
		{
			if (p == NULL || p->next == NULL) return end();
			linklist_node<T> *np = new linklist_node<T>(p, p->next, tdata);
			p->next->prev = np;
			p->next = np;
			++length;
			_resetnow();
			return Iterator(np);
		}
		/**
		@brief 插入一个数据\n
		@param[in] p 待插入位置的前一个下标
		@param[in] tdata 待插入的数据
		@retval 指向插入节点的迭代器
		*/
		Iterator insert(SIsize_t p, const T& tdata)
		{
			if (!_movenow(p)) return end();
			linklist_node<T> *np = new linklist_node<T>(nowp, nowp->next, tdata);
			nowp->next->prev = np;
			nowp->next = np;
			++length;
			return Iterator(np);
		}
		/**
		@brief 插入一个数据\n
		@param[in] p 待插入位置的前一个指针
		@param[in] tdata 待插入的数据
		@retval 指向插入节点的迭代器
		*/
		Iterator insert(Iterator it, const T& tdata)
		{
			insert(it.p, tdata);
			return ++it;
		}
		/**
		@brief 删除一个节点\n
		@param[in] it 指向待删除节点的迭代器
		@rtnval 指向待删除节点后一个节点的迭代器
		*/
		Iterator erase(Iterator it)
		{
			return erase(it.p);
		}
		Iterator remove(Iterator it)	///<要求实现的接口
		{
			return erase(it.p);
		}
		/**
		@brief 删除一个节点\n
		@param[in] it 指向待删除节点的指针
		@rtnval 指向待删除节点后一个节点的迭代器
		*/
		Iterator erase(linklist_node<T>* p)
		{
			if (p->prev == NULL || p->next == NULL) return end();
			Iterator rtn(p->next);
			p->prev->next = p->next;
			p->next->prev = p->prev;
			delete p;
			--length;
			_resetnow();
			return rtn;
		}
		/**
		@brief 删除一个节点\n
		@param[in] it 待删除节点的下标
		@rtnval 指向待删除节点后一个节点的迭代器
		*/
		Iterator erase(SIsize_t p)
		{
			if (!_movenow(p)) return end();
			linklist_node<T>* pp = nowp;
			nowp = nowp->next;
			pp->prev->next = pp->next;
			pp->next->prev = pp->prev;
			delete pp;
			--length;
			return Iterator(nowp);
		}
		/**
		@brief 删除一段节点\n
		@param[in] ps 指向待删除节点段开始节点的指针
		@param[in] pe 指向待删除节点段结束节点的指针
		@rtnval 指向待删除节点段结束节点的后一个节点的迭代器
		*/
		Iterator erase(linklist_node<T>* ps, linklist_node<T>* pe)
		{
			if (ps->prev == NULL || pe->next == NULL) return end();

			Iterator rtn(pe->next);

			pe->next->prev = ps->prev;

			SIsize_t cnt = 0;

			linklist_node<T>* brd = ps->prev;
			linklist_node<T>* p;
			for (p = pe->prev; p != brd; p = p->prev, ++cnt)
				delete p->next;
			delete p->next;
			p->next = rtn.p;
			length -= (cnt + 1);

			_resetnow();

			return rtn;
		}
		/**
		@brief 删除一段节点\n
		@param[in] ps 待删除节点段开始节点的下标
		@param[in] pe 待删除节点段结束节点的下标
		@rtnval 指向待删除节点段结束节点的后一个节点的迭代器
		*/
		Iterator erase(SIsize_t is, SIsize_t ie)
		{
			linklist_node<T>* ps;
			linklist_node<T>* pe;
			SIsize_t cnt = 0;

			if (!_movenow(ie)) return end();
			pe = nowp;
			Iterator rtn(pe->next);
			if (!_movenow(is)) return end();
			ps = nowp;
			nowp = nowp->prev;
			--nowid;

			pe->next->prev = ps->prev;

			linklist_node<T>* brd = ps->prev;
			linklist_node<T>* p;
			for (p = pe->prev; p != brd; p = p->prev, ++cnt)
				delete p->next;
			delete p->next;
			p->next = rtn.p;

			length -= (cnt + 1);

			return rtn;
		}

		/**
		@brief 删除一段节点\n
		@param[in] ps 指向待删除节点段开始节点的迭代器
		@param[in] pe 指向待删除节点段结束节点的迭代器
		@rtnval 指向待删除节点段结束节点的后一个节点的迭代器
		*/
		Iterator erase(Iterator its, Iterator ite)
		{
			return erase(its.p, ite.p);
		}

		/**
		@brief 在链表末尾追加一个元素\n
		@param[in] tdata 要追加的元素
		@retval 指向链表最后一个节点的迭代器
		*/
		Iterator push_back(const T& tdata)
		{
			linklist_node<T> *p = tail->prev;
			linklist_node<T> *np = new linklist_node<T>(p, p->next, tdata);
			p->next->prev = np;
			p->next = np;
			++length;
			return Iterator(np);
		}
		void push_back(linklist<T>& tlist)
		{
			/*
			linklist_node<T> *p = tail->prev;
			linklist_node<T> *np = new linklist_node<T>(p, p->next, tdata);
			p->next->prev = np;
			p->next = np;
			++length;
			return Iterator(np);
			*/
			for (linklist<T>::Iterator it = tlist.begin(); it != tlist.end(); ++it)
				push_back(*it);
		}
		Iterator add(const T& tdata)	///<要求实现的接口
		{
			linklist_node<T> *p = tail->prev;
			linklist_node<T> *np = new linklist_node<T>(p, p->next, tdata);
			p->next->prev = np;
			p->next = np;
			++length;
			return Iterator(np);
		}
		Iterator search(const T& tdata)	///<要求实现的接口
		{
			for (Iterator it = begin(); it != end(); ++it)
				if ((*it) == tdata) return it;
			return Iterator(NULL);
		}
		void pop_back();	///<删除链表的最后一个元素
		void append();	///<增加链表长度
		void append(SIsize_t k);
		void print();
		T& operator [] (SIsize_t i);	///<重载下标运算符 
		linklist& operator = (linklist& tlist)	///< 重载赋值运算符
		{
			destroy();
			head = new linklist_node<T>();
			tail = new linklist_node<T>();
			defaultp = new linklist_node<T>();
			head->next = tail;
			tail->prev = head;
			nowp = head;
			nowid = -1;
			length = 0;

			int tsize = tlist.size();
			append(tsize);
			for (int i = 0; i < tsize; ++i)
				(*this)[i] = (tlist[i]);
			return *this;
		}

		SIsize_t size() const;	///<得到链表的长度

		void read();
		void read(SIsize_t n);
		void exchange(linklist_node<T>* p1, linklist_node<T>* p2);
		/**
		@brief 链表元素排序\n
		@param[in] cmp 自定义元素比较函数
		*/
		void sort(bool(*cmp)(const T&, const T&));	

		Iterator begin()	///<得到指向链表第一个节点的迭代器
		{
			return Iterator(head->next);
		}
		Iterator end()	///<得到指向链表最后一个节点的下一个节点的迭代器
		{
			return Iterator(tail);
		}
	};

	template<typename T>
	std::ostream& operator << (std::ostream& fout, const linklist<T>& tlist)
	{
		for (linklist_node<T>* p = tlist.head->next; p != tlist.tail; p = p->next)
			fout << (*p) << std::endl;
		return fout;
	}

	template<typename T>
	class linklist<T>::Iterator
	{
		friend class linklist<T>;
	private:
		linklist_node<T> *p;
	public:
		Iterator() :p(NULL) {}
		Iterator(linklist_node<T>* tp) :p(tp) {}

		bool operator == (const Iterator& tit)	///<重载相等运算符
		{
			return p == tit.p;
		}
		bool operator != (const Iterator& tit)	///<重载不等运算符
		{
			return p != tit.p;
		}
		Iterator& operator ++()	///<重载前置自增运算符
		{
			p = p->next;
			return *this;
		}
		const Iterator operator ++(int)	///<重载后置自增运算符
		{
			Iterator rtn = *this;
			p = p->next;
			return rtn;
		}
		Iterator& operator --()	///<重载前置自减运算符
		{
			p = p->prev;
			return *this;
		}
		const Iterator operator --(int)	///<重载后置自减运算符
		{
			Iterator rtn = *this;
			p = p->prev;
			return rtn;
		}
		friend T& operator *(const Iterator& it)	///<重载解引用运算符
		{
			return *((it.p)->pdata);
		}

		void Edit(linklist_node<T>* p, const T& tdata)
		{
			(*p->pdata) = tdata;
		}
	};
}

template<typename T>
SI::linklist_node<T>::linklist_node(linklist_node<T>* tprev, linklist_node<T>* tnext, const T& tdata) :prev(tprev), next(tnext)
{
	pdata = new T(tdata);
}

template<typename T>
SI::linklist_node<T>::linklist_node(linklist_node<T>* tprev, linklist_node<T>* tnext) :prev(tprev), next(tnext)
{
	pdata = new T();
}

template<typename T>
SI::linklist_node<T>::linklist_node(const T& tdata) :prev(NULL), next(NULL)
{
	pdata = new T(tdata);
}

template<typename T>
SI::linklist_node<T>::linklist_node() :prev(NULL), next(NULL)
{
	pdata = new T();
}

template<typename T>
SI::linklist_node<T>::~linklist_node()
{
	delete pdata;
}

template<typename T>
void SI::linklist_node<T>::print()
{
	pdata->print();
}
template<typename T>

bool SI::linklist_node<T>::read()
{
	return pdata->read();
}

template<typename T>
SI::linklist<T>::linklist()
{
	head = new linklist_node<T>();
	tail = new linklist_node<T>();
	defaultp = new linklist_node<T>();
	head->next = tail;
	tail->prev = head;
	nowp = head;
	nowid = -1;
	length = 0;
}
template<typename T>
SI::linklist<T>::~linklist()
{
	destroy();
}
template<typename T>
void SI::linklist<T>::_clear()
{
	for (linklist_node<T>* p = head->next; p != tail; p = p->next)
		delete p->prev;
	delete tail;
	delete defaultp;

	head = new linklist_node<T>();
	tail = new linklist_node<T>();
	defaultp = new linklist_node<T>();
	head->next = tail;
	tail->prev = head;
	nowp = head;
	nowid = -1;
	length = 0;

}

template<typename T>

void SI::linklist<T>::_resetnow()
{
	nowp = head;
	nowid = -1;
}

template<typename T>
bool SI::linklist<T>::_movenow(SIsize_t p)
{
	if (p < 0 || p >= length) return false;
	for (; p > nowid; ++nowid) nowp = nowp->next;
	for (; p < nowid; --nowid) nowp = nowp->prev;
	return true;
}

template<typename T>
void SI::linklist<T>::pop_back()
{
	if (length) erase(tail->prev);
}

template<typename T>
void SI::linklist<T>::append()
{
	push_back(T());
}

template<typename T>
void SI::linklist<T>::append(SIsize_t k)
{
	if (k <= 0) return;
	length += k;
	linklist_node<T> *ps = new linklist_node<T>;
	linklist_node<T> *pe = ps;
	for (--k; k; --k)
	{
		pe->next = new linklist_node<T>(pe, NULL);
		pe = pe->next;
	}
	ps->prev = tail->prev;
	pe->next = tail;
	tail->prev->next = ps;
	tail->prev = pe;
}

template<typename T>
void SI::linklist<T>::print()
{
	for (linklist_node<T> *p = head->next; p != tail; p = p->next, putchar('\n'))
		p->print();
}

template<typename T>
T& SI::linklist<T>::operator [] (SIsize_t i)
{
	if (!_movenow(i)) return *(defaultp->pdata);
	return (*(nowp->pdata));
}

template<typename T>
void SI::linklist<T>::read()
{
	T tdata;
	_clear();
	while (tdata.read())
	{
		++length;
		push_back(tdata);
	}
}

template<typename T>
void SI::linklist<T>::read(SIsize_t n)
{
	if (n < 0) return;
	_clear();
	T tdata;
	for (length = n; n; --n)
	{
		tdata.read();
		push_back(tdata);
	}
}

template<typename T>
SI::SIsize_t SI::linklist<T>::size() const
{
	return length;
}

template<typename T>
void SI::linklist<T>::exchange(linklist_node<T>* p1, linklist_node<T>* p2)
{
	p1->prev->next = p1->next->prev = p2;
	p2->prev->next = p2->next->prev = p1;

	linklist_node<T> *tprev, *tnext;

	tprev = p1->prev;
	tnext = p1->next;

	p1->prev = p2->prev;
	p1->next = p2->next;

	p2->prev = tprev;
	p2->next = tnext;
}

template<typename T>
void SI::linklist<T>::sort(bool(*cmp)(const T&, const T&))
{
	T* tpdata;
	if (length <= 1) return;
	linklist_node<T>* p;
	for (SIsize_t i = 0; i != length; ++i)
		for (p = head->next; p->next != tail; p = p->next)
			if (!(*cmp)(*(p->pdata), *(p->next->pdata)))
			{
				tpdata = p->pdata;
				p->pdata = p->next->pdata;
				p->next->pdata = tpdata;
			}
}

#endif //LINKLIST_H