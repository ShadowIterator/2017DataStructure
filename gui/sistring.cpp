#include "stdafx.h"
#include"sistring.h"
#include"si_global.h"

namespace SI
{
	const SIsize_t SIString::INITCAP = 128;
	const SIsize_t SIString::DELTACAP = 2;
	const SIchar_t SIString::MASK = (1 << 8) - 1;
	const SIchar_t SIString::COMMA = 0xA3AC;
	std::map<SIchar_t, SIchar_t> SIString::UnicodeToGBK;
	std::map<SIchar_t, SIchar_t> SIString::GBKtoUnicode;

	SIchar_t SIString::transCode(char chh, char chl)
	{
		return (SIchar_t)((((short)(chh)) << 8) | (((short)(chl)) & MASK));
	}

	SIchar_t SIString::transCode(char ch)
	{
		return (SIchar_t)((short)(ch));
	}

	SIString::SIString(const char* s) :capacity(0), size(0), data(NULL)
	{
		fromCstr(s);
	}

	SIString::SIString(const std::string& s) :capacity(0), size(0), data(NULL)
	{
		fromString(s);
	}

	SIString::SIString() :data(NULL), capacity(INITCAP), size(0)
	{
		data = new SIchar_t[INITCAP];
	}

	SIString::SIString(SIsize_t tcapacity) : capacity(tcapacity), size(0)
	{
		data = new SIchar_t[tcapacity];
	}

	SIString::SIString(const SIString& tstr) : data(NULL), capacity(0), size(0)
	{
		this->assign(tstr);
	}

	SIString::~SIString()
	{
		if (data != NULL) delete[] data;
		data = NULL;
	}

	bool SIString::checkBlank()
	{
		for (SIsize_t i = 0; i < size; ++i)
			if (!isblank(data[i])) return false;
		return true;
	}

	void SIString::transComma()
	{
		for (SIsize_t i = 0; i < size; ++i)
			if (data[i] == transCode(','))
				data[i] = COMMA;
	}

	SIchar_t SIString::_transEscapeSeq_SIchar(const SIString& str, int& i)
	{
		++i;
		SIString temp(8);
		if (str[i] == '#')
		{
			int decUnicode = 0;
			for (++i; str[i] != ';'; ++i) decUnicode = decUnicode * 10 + str[i] - '0';
			return SIchar_t(UnicodeToGBK[decUnicode]);
		}
		else
		{
			for (; str[i] != ';'; ++i) temp += str[i];
			if (temp == "quot")
				return transCode('\'');
			else if (temp == "amp")
				return transCode('&');
			else if (temp == "lt")
				return transCode('<');
			else if (temp == "gt")
				return transCode('>');
			else if (temp == "nbsp")
				return transCode(' ');
		}
		return transCode('$');
	}

	SIString SIString::transEscapeSeq(const SIString& str)
	{
		SIString rtn;
		rtn.clear();
		int len = str.getsize();
		for (int i = 0; i < len; ++i)
		{
			if (str[i] == '&') rtn += _transEscapeSeq_SIchar(str, i);
			else rtn += str[i];
		}
		return rtn;
	}

	void SIString::fromCstr(const char* s)
	{
		SIsize_t len = 0;
		for (; s[len] != '\0'; ++len);
		capacity = Max(len, capacity);
		if (data != NULL) delete[] data;
		data = new SIchar_t[capacity];

		size = charToSIchar(s, len, data);
	}

	void SIString::fromString(const std::string& s)
	{
		fromCstr(s.c_str());
	}

	void SIString::fromCString(const CString& s)
	{
		SIsize_t len = s.GetLength();
		//capacity = Max(len, capacity);
		if (len > capacity || data == NULL)
		{
			capacity = len;
			if (data != NULL) delete[] data;
			data = new SIchar_t(capacity);
		}
		for (SIsize_t i = 0; i < len; ++i) data[i] = s[i];
		size = len;
	}

	inline int SIString::charToSIchar(const char* s, SIsize_t slen, SIchar_t *pws)
	{
		int wlen = 0;
		for (int i = 0; i < slen; ++i)
		{
			if (ischar(s[i])) pws[wlen++] = (wchar_t)((short)(s[i]));
			else
			{
				pws[wlen++] = transCode(s[i], s[i + 1]);
				++i;
			}
		}
		return wlen;
	}

	inline int SIString::SIcharTochar(const SIchar_t* pws, SIsize_t wlen, char* s)
	{
		int slen = 0;
		for (int i = 0; i < wlen; ++i)
		{
			if (ischar(pws[i])) s[slen++] = (char)(pws[i]);
			else
			{
				s[slen++] = (char)(((short)(pws[i]) >> 8) & MASK);
				s[slen++] = (char)((short)(pws[i]) & MASK);
			}
		}
		s[slen++] = '\0';
		return slen - 1;
	}

	bool SIString::operator != (const SIString& tstr)
	{
		return !((*this) == tstr);
	}

	SIchar_t* SIString::getdata()
	{
		return data;
	}

	SIchar_t* SIString::getdatac() const
	{
		return data;
	}

	SIsize_t SIString::getsize() const
	{
		return size;
	}

	SIsize_t SIString::indexOf(const SIString& s)
	{
		return indexOf(s.getdatac(), s.getsize());
	}

	SIsize_t SIString::indexOf(const SIchar_t* s)
	{
		int len;
		for (len = 0; s[len] != '\0'; ++len);
		return indexOf(s, len);
	}

	SIsize_t SIString::indexOf(const SIchar_t* s, SIsize_t ssize)
	{
		SIsize_t *f = new SIsize_t[ssize];
		f[0] = -1;
		SIsize_t fail;
		for (int i = 1; i < ssize; ++i)
		{
			fail = f[i - 1];
			while (fail != -1 && s[fail + 1] != s[i]) fail = f[fail];
			if (s[fail + 1] == s[i]) f[i] = fail + 1;
			else f[i] = -1;
		}
		int j = -1;
		for (int i = 0; i < size; ++i)
		{
			while (j != -1 && s[j + 1] != data[i]) j = f[j];
			if (s[j + 1] == data[i]) ++j;
			else j = -1;
			if (j == ssize - 1) return i - ssize + 1;
		}
		return -1;
	}

	void SIString::concat(const SIString& tstr)
	{
		if (capacity < (size + tstr.size))
		{
			SIchar_t* pt = data;
			capacity = Max(capacity, tstr.capacity) * DELTACAP;
			data = new SIchar_t[capacity];
			memcpy(data, pt, size * sizeof(SIchar_t));
			delete[] pt;
		}
		memcpy(data + size, tstr.data, tstr.size * sizeof(SIchar_t));
		size += tstr.size;
	}

	void SIString::concat(const SIchar_t& ch)
	{
		if (capacity < (++size))
		{
			SIchar_t* pt = data;
			capacity *= DELTACAP;
			data = new SIchar_t[capacity];
			memcpy(data, pt, (size - 1) * sizeof(SIchar_t));
			delete[] pt;
		}
		data[size - 1] = ch;
	}

	void SIString::assign(const SIString& tstr)
	{
		if (capacity != tstr.capacity)
		{
			capacity = tstr.capacity;
			if (data != NULL)
				delete[] data;
			data = new SIchar_t[capacity];
		}
		size = tstr.size;
		memcpy(data, tstr.data, size * sizeof(SIchar_t));
	}

	void SIString::reverse()
	{
		if (size <= 1) return;
		for (SIsize_t i = ((size >> 1) - 1); i >= 0; --i)
			_exchange_xor(data[i], data[size - i - 1]);
	}

	SIString SIString::substring(SIsize_t st, SIsize_t len) const
	{
		SIsize_t rlen = Min(len, size - st);
		SIString rtn(capacity);
		rtn.size = rlen;
		memcpy(rtn.data, data + st, rlen * sizeof(SIchar_t));
		return rtn;
	}

	bool SIString::operator == (const SIString& tstr)
	{
		if (size != tstr.size) return false;
		SIchar_t *p1, *p2; int i;
		for (p1 = data, p2 = tstr.data, i = 0; i < size; ++i, ++p1, ++p2)
			if ((*p1) != (*p2)) return false;
		return true;
	}

	SIString& SIString::operator = (const SIString& tstr)
	{
		assign(tstr);
		return *this;
	}
	
	SIString SIString::operator + (const SIString& adder)
	{
		SIString rtn(*this);
		rtn.concat(adder);
		return rtn;
	}

	bool SIString::operator < (const SIString& tstr)
	{
		SIchar_t* datac = tstr.getdatac();
		SIsize_t minlen = Min(size, tstr.getsize());
		for (SIsize_t i = 0; i < minlen; ++i)
			if (data[i] < datac[i]) return true;
			else if (data[i] > datac[i]) return false;
		return size < tstr.getsize();
	}

	bool SIString::operator > (const SIString& tstr)
	{
		SIchar_t* datac = tstr.getdatac();
		SIsize_t minlen = Min(size, tstr.getsize());
		for (SIsize_t i = 0; i < minlen; ++i)
			if (data[i] > datac[i]) return true;
			else if (data[i] < datac[i]) return false;
			return size > tstr.getsize();
	}


	SIString& SIString::operator += (const SIString& adder)
	{
		concat(adder);
		return *this;
	}

	SIString& SIString::operator += (const SIchar_t& ch)
	{
		concat(ch);
		return *this;
	}

	SIchar_t& SIString::operator [] (SIsize_t index)
	{
		return data[index];
	}

	SIchar_t SIString::operator [] (SIsize_t index) const
	{
		return data[index];
	}

	std::ostream& operator << (std::ostream& out, const SIString& str)
	{
		SIsize_t len = 0, strlen = str.size;
		char* buff = new char[((str.size) << 1) + 2];
		SIString::SIcharTochar(str.data, str.size, buff);
		out << buff;
		delete[] buff;
		return out;
	}

	bool operator < (const SIString& s1, const SIString& s2)
	{
		SIchar_t* sa = s1.getdatac();
		SIchar_t* sb = s2.getdatac();
		SIsize_t lena = s1.getsize();
		SIsize_t lenb = s2.getsize();
		SIsize_t minl = Min(lena, lenb);
		for (int i = 0; i < minl; ++i)
			if (sa[i] < sb[i]) return true;
			else if (sa[i] > sb[i]) return false;
		return lena < lenb;
	}

	void SIString::clear()
	{
		size = 0;
	}

	SIStringList SIString::split(SIchar_t sym)
	{
		SIStringList rtn;
		SIString temp;
		int i;
		SIchar_t* pt;
		for (pt = data, i = 0; i < size; ++i, ++pt)
		{
			if ((*pt) == sym)
			{
			//	std::cout << temp << std::endl;

				rtn.push_back(temp);
				temp.clear();
				while (i < size && (*pt) == sym) ++pt, ++i;
				--pt; --i;
			}
			else temp.concat(*pt);
		}
		rtn.push_back(temp);
		return rtn;
	}
	
	SIchar_t SIString::_HexToDec_digi(char ch)
	{
		if ('0' <= ch&&ch <= '9') return ch - '0';
		return ch - 'A' + 10;
	}

	SIchar_t SIString::_HexToDec(std::string num)
	{
		SIchar_t rtn = 0;
		for (int i = 0; i < num.size(); ++i)
			rtn = rtn * 16 + _HexToDec_digi(num[i]);
		return rtn;
	}

	int SIString::toNumber()
	{
		bool flag = false;
		int rtn = 0;
		int i;
		for (i = 0; i < size && data[i]<'0' && data[i]>'9'; ++i)
			if (data[i] == '-') flag = true;
		for (; i < size && '0' <= data[i] && data[i] <= '9'; ++i)
			rtn = rtn * 10 + data[i] - '0';
		if (flag) rtn = -rtn;
		return rtn;
	}

	void SIString::init(const char* infile)
	{
		std::ifstream fin;
		fin.open(infile);
		std::string str;
		int unicode;
		int gbk;
		while (fin >> str)
		{
			UnicodeToGBK[unicode = _HexToDec(str.substr(0, 4))] = (gbk = _HexToDec(str.substr(5, 4)));
			GBKtoUnicode[gbk] = unicode;
		}
	}

	int SIString::hash(int P) const
	{
		int rtn = 0;
		for (SIsize_t i = 0; i < size; ++i)
			rtn = (rtn + data[i]) % P;
		return rtn;
	}

	SIString SIString::toUnicode()
	{
		SIString rtn;
		rtn.clear();
		SIchar_t ch;

		for (int i = 0; i < size; ++i)
		{
			ch = data[i];
			if (ischar(ch))	rtn += ch;
			else
				rtn+= GBKtoUnicode[ch];
		}
		return rtn;
	}

	void SIString::txUnicode()
	{
		for (int i = 0; i < size; ++i)
			if (!ischar(data[i])) data[i] = GBKtoUnicode[data[i]];
	}
	void SIString::txGBK()
	{
		for (int i = 0; i < size; ++i)
			if (!ischar(data[i])) 
				data[i] = UnicodeToGBK[data[i]];
	}
	
}
