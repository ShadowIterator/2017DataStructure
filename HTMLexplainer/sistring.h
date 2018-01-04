#ifndef SISTRING_H
#define SISTRING_H

/**
@brief 字符串\n
@file sistring.h
@author ShadowIterator
@email ShadowIterator@hotmail.com
@version 0.1
@date 2017.11.12
*/

#include"si_global.h"
#include"linklist.h"

namespace SI
{
	typedef linklist<SIString> SIStringList; ///<定义字符串链表

	/**
	@brief 字符串类\n
	*/
	class SIString	
	{
	private:
		SIsize_t capacity;	///<字符串的容量
		SIsize_t size;	///<字符串长度
		SIchar_t *data;	///<存放字符串的空间
	public:
		static const SIchar_t MASK;
		static const SIsize_t INITCAP;
		static const SIsize_t DELTACAP;
		static const SIchar_t COMMA;
		static SIchar_t SPACE;
		static SIchar_t TAB;
		static SIchar_t ENTER;
		static std::map<SIchar_t, SIchar_t> UnicodeToGBK;	///<UniCode到GBK的对照表,用于把Unicode编码转换为GBK编码
	public:
		static void init(const char* infile);	///<初始化
		static SIchar_t _HexToDec(std::string num);	///<十六进制转十进制
		static SIchar_t _HexToDec_digi(char ch);
		SIString();
		SIString(SIsize_t tcapacity);
		SIString(const char* s);
		SIString(const SIString& tstr);	///<拷贝构造函数
		SIString(const std::string& s);
		~SIString();

		void fromCstr(const char* s);	///<把一个C风格字符串转换为SIString
		void fromString(const std::string& s);	///<把一个std::string转换为SIString

		static int charToSIchar(const char* s, SIsize_t slen, SIchar_t *pws);	///<把一个char的数组转换为SIchar_t的数组
		static int SIcharTochar(const SIchar_t* pws, SIsize_t wlen, char* s);	///<把一个SIchar_t的数组转换为char的数组
		static SIchar_t _transEscapeSeq_SIchar(const SIString& str, int& i);	///<把网页中转义的一个Unicode编码的汉字转化为GBK编码的汉字
		static SIString transEscapeSeq(const SIString& str);	///<把字符串中转义的所有Unicode编码的汉字转化为GBK编码的汉字

		template<class T>
		static bool ischar(T ch)	///<判断一个字符是否在ASCII表示的范围内
		{
			return 0 <= ch && ch < 128;
		}

		template<class T>
		static bool isblank(T ch)	///<判断一个字符是否是空格、换行、制表符
		{
			return
				ch == transCode('\n') || ch == transCode('\r') ||
				ch == transCode('\v') || ch == transCode('\t') ||
				ch == transCode(' ');
		}

		template<class T>
		static bool isenter(T ch)	///<判断一个字符是否是换行
		{
			return ch == transCode('\n') || ch == transCode('\r');
		}

		template<class T>
		static bool isstopsym(T ch)	///<判断一个字符是否是分隔符
		{
			return isblank(ch) || ch == ',' || ch == '.' || ch == '\'' || ch == '\"';
		}

		template<class T>
		static bool isdigit(T ch)	///<判断一个字符是否是数字
		{
			return transCode('0') <= ch&&ch <= transCode('9');
		}
		static SIchar_t transCode(char chh, char chl);	///<把两位char转换为一位SIchar_t
		static SIchar_t transCode(char ch);	///<把一位char转换为一位SIchar_t
		/**
		@brief 清空字符串\n
		@note 字符串的容量和占用空间不会改变
		*/
		void clear();
		void transComma();
		bool checkBlank();
		SIchar_t* getdata();
		SIsize_t getsize() const;
		SIchar_t* getdatac() const;
		/**
		@brief 用KMP算法做子串匹配\n
		@note 要求实现的接口
		@param[in] s 模式串
		@retval s在当前串中第一次出现的位置
		*/
		SIsize_t indexOf(const SIString& s);
		SIsize_t indexOf(const SIchar_t* s);
		SIsize_t indexOf(const SIchar_t* s,SIsize_t ssize);
		/**
		@brief 返回当前串的一个子串\n
		@note 要求实现的接口
		@param[in] st 子串的起始下标
		@retval len 子串的长度
		*/
		SIString substring(SIsize_t st, SIsize_t len) const;
		/**
		@brief 在当前串后面连接一个字符串\n
		@note 要求实现的接口
		@param[in] tstr 连接串
		*/
		void concat(const SIString& tstr);
		void concat(const SIchar_t& ch);
		void assign(const SIString& tstr);	///<要求实现的接口
		void reverse();	///<字符串翻转
		/**
		@brief 字符串分割函数\n
		@param[in] sym 作为分割标记的字符
		*/
		SIStringList split(SIchar_t sym);

		SIString& operator += (const SIString& adder);
		SIString& operator += (const SIchar_t& ch);
		SIString operator + (const SIString& adder);
		bool operator == (const SIString& tstr);
		bool operator < (const SIString& tstr);
		bool operator != (const SIString& tstr);
		SIString& operator = (const SIString& tstr);
		SIchar_t& operator [] (SIsize_t index);
		SIchar_t operator [](SIsize_t index) const;
		friend std::ostream& operator << (std::ostream& out, const SIString& str);
		friend bool operator < (const SIString& s1, const SIString& s2);
	};

}

#endif //SISTRING_H