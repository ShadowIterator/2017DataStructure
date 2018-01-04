#ifndef STACK_H
#define STACK_H

/**
@brief 栈\n
@file stack.h
@author ShadowIterator
@email ShadowIterator@hotmail.com
@version 0.1
@date 2017.11.12
*/


#include"si_global.h"
#include"linklist.h"

namespace SI
{
	template<class T>
	/**
	@brief 栈\n
	就是把链表封装了一下
	*/
	class Stack
	{
	private:
		linklist<T> stk;
	public:
		Stack():stk()
		{
			
		}
		~Stack()
		{

		}
		void _clear()
		{
			stk._clear();
		}
		SIsize_t size()
		{
			return stk.size();
		}
		void push(T tdata)
		{
			stk.push_back(tdata);
		}
		void pop()
		{
			stk.pop_back();
		}
		T top()
		{
			if (stk.empty()) return T();
			return *(stk.tail->prev->pdata);
		}
		bool empty()
		{
			return stk.empty();
		}

		friend std::ostream& operator << (std::ostream& fout,const Stack& x)
		{
			return fout << x.stk;
		}
	};
}
#endif //STACK_H