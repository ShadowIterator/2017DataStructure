#ifndef SEGMENTATIONER_H
#define SEGMENTATIONER_H

/**
@brief 分词\n
@file segmentationer.h
@author ShadowIterator
@email ShadowIterator@hotmail.com
@version 0.1
@date 2017.11.11
*/

#include"si_global.h"
#include"sistring.h"
#include"acauto.h"
namespace SI
{
	class Segmentationer
	{
	private:
		static ACAuto T;	///<存放字典的AC自动机
		static char* buff;	///<输入缓冲区
		static int* f;	///<用于DP的suzuki
		static int* prev;
		static int tot;
		static int* last;
		static int* next;
		static int* st;
	public:
		static const int MAX_LEN;	///<字符串最大长度
		static const int MAX_MATCH;	///<匹配区间的最大数量
		static const SIsize_t BUFF_SIZE;	///<默认输入缓冲区大小
	public:
		Segmentationer();

		template<class T>
		static T* _alloc(T* ptr, SIsize_t size)	///<申请空间
		{
			if (ptr != NULL) delete[] ptr;
			return new T[size];
		}
		template<class T>
		static void _destroy(T* ptr)	///<释放空间
		{
			if (ptr != NULL) delete[] ptr;
			ptr = NULL;
		}
		static void addrange(int s, int e);
		static void allocBuff(SIsize_t size);	///<申请空间
		static void destroyBuff();	///<释放空间
		static void loadDic(char* infile);	///<加载字典
		static SIStringList _doSegmentation(SIString&);	
		/**
		@brief 分词函数\n
		@param[in] contents 待分词的字符串
		@retval 分词结果
		*/
		static SIStringList doSegmentation(SIString& contents);
	};
}

#endif //SEGMENTATIONER_H