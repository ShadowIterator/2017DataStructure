#include"si_global.h"
#include"element.h"

namespace SI
{
	char Element::LABEL = 0;
	char Element::CONTENT = 1;

	Element::Element() :type(LABEL), contents(), properties()
	{

	}

	Element::Element(char ttype, const SIString& info) : type(ttype)
	{
		assign(ttype, info);
	}

	Element::~Element()
	{

	}

	void Element::assign(char ttype, const SIString& info)
	{
		type = ttype;
		properties.clear();
		int i, len, j;
		if (type == LABEL)
		{
			for (i = 0, len = info.getsize(); i < len && SIString::isblank(info[i]); ++i);
			for (j = i; j < len && (!isblank(info[j])); ++j);
			contents.assign(info.substring(i, j - i));
			analyzePro(info.substring(j, len - j));
		}
		else contents.assign(info);
	}

	void Element::analyzePro(const SIString& info)
	{
		int i = 0 , j, len;
		int keys,keye, vals,vale;
		len = info.getsize();
		while (i < len)
		{
			while (SIString::isblank(info[i])) ++i;
			if (info[i] == '>') return;
			for (j = i; j < len&&info[j] != '=' && !(SIString::isblank(info[j])); ++j);
			keys = i; keye = j - 1;
			while (j < len&&info[j] != '=') ++j;
			for (++j; j < len && info[j] != '>' && info[j] != '\"'; ++j);
			if (info[j] == '>') return;
			for (i = ++j; j < len&&info[j] != '\"'; ++j);
			vals = i; vale = j - 1;
			if (keye >= keys && vale >= vals) properties[info.substring(keys, keye - keys + 1)] = info.substring(vals, vale - vals + 1);
			i = j + 1;
		}
	}
}