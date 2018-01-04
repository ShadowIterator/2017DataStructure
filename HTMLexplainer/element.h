#ifndef ELEMENT_H
#define ELEMENT_H

/**
@brief 网页元素\n
@file element.h
@author ShadowIterator
@email ShadowIterator@hotmail.com
@version 0.1
@date 2017.11.12
*/

#include"si_global.h"
#include"sistring.h"

namespace SI
{
	/**
	@brief 网页元素类\n
	网页上的标签和非标签内容都抽象为一个\"元素\"
	*/
	class Element
	{
	public:
		char type;	///<标识这个元素是否是标签
		std::map<SIString, SIString> properties;	///<如果这个元素是标签，那么解析它的属性(如class,id等)到这个成员中
		SIString contents;	///<标签的名字或者一段"内容"
	public:
		
		Element();	///<构造函数1
		Element(char ttype,const SIString& info);	///<构造函数2
		~Element();	///<析构函数
		/**
		@brief 属性解释函数\n
		@param[in] info 一个长字符串，包含标签中除了名字之外的部分
		*/
		void analyzePro(const SIString& info);
		/**
		@brief 从一个字符串构造一个元素\n
		@param[in] ttype 元素的类型
			-0 标签
			-1 内容
		@param[in] info 一个字符串，等于一个<>内的字符串或者一段内容
		*/
		void assign(char ttype, const SIString& info);
		static char LABEL;
		static char CONTENT;
	};
}

#endif //ELEMENT_H