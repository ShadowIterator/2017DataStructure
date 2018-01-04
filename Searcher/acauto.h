#ifndef ACAUTO_H
#define ACAUTO_H

/**
@brief AC自动机\n
@file acauto.h
@author ShadowIterator
@email ShadowIterator@hotmail.com
@version 0.1
@date 2017.11.11
*/

#include"si_global.h"
#include"sistring.h"

namespace SI
{
	
	/**
	@brief AC自动机节点\n
	*/
	class _ACAuto_Node
	{
	public:
		_ACAuto_Node* fail;	///<fail指针
		std::map<SIchar_t, _ACAuto_Node*> son;	///<转移
		SIsize_t len;	///<匹配长度
		bool endOfString;	///<是否是一个字符串
	public:
		_ACAuto_Node();	///<构造函数
	};

	/**
	@brief AC自动机\n
	*/
	class ACAuto
	{
		typedef _ACAuto_Node node;
		typedef _ACAuto_Node* nodeptr;
	private:
		static std::queue<nodeptr> q;
	public:
		nodeptr root;	///<根节点
	public:
		ACAuto();	///<构造函数
		void insertString(const SIString& s);	///<在当前的Trie中插入一个字符串
		void calcFail();	///<计算fail指针
	};
}

#endif //ACAUTO_H