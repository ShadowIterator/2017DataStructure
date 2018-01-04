#ifndef SELFCLOSEDLABELCHECKER_H
#define SELFCLOSEDLABELCHECKER_H

/**
@brief 处理自闭合标签\n
@file selfclosedlabelchecker.h
@author ShadowIterator
@email ShadowIterator@hotmail.com
@version 0.1
@date 2017.11.11
*/

#include"si_global.h"
#include"sistring.h"

namespace SI
{
	class SelfClosedLabelChecker
	{
	public: 
		const static SIsize_t BUFF_SIZE;	///<默认输入缓冲区大小
	private:
		static char* buff;	///<输入缓冲区
		static SIStringList labellist;	///<自闭合标签列表
	public:
		static void allocBuff(SIsize_t buffsize);	///<申请输入缓冲区空间
		static void destroyBuff();	///<释放输入缓冲区标签
		static void init(char* infile);	///<初始化函数
		static bool check(const SIString& str);	///<检查一个标签是否是自闭合标签
	};
}
#endif //SELFCLOSEDLABELCHECKER_H