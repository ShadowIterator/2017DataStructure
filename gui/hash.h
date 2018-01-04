#ifndef HASH_H
#define HASH_H

#include"si_global.h"
#include"linklist.h"

namespace SI
{
	const int MAXP = 1 << 22;
	const int DEFAULTP = 4194301;
	const int DEFAULTSIGMA = 65537;

	template<typename T>
	class HASH
	{
	public:
		int P;
		int sigma;
		linklist<T> data[MAXP];
		
		HASH() :P(DEFAULTP),sigma(DEFAULTSIGMA) {}
		HASH(int tP,int tsigma) :P(tP),sigma(tsigma) {}
		HASH(int tsigma) :P(DEFAULTP), sigma(tsigma) {}

		T* insert(const T& tdata)
		{
			int id = tdata.hash(P);
			linklist<T>* ptr = &data[id]; 
			linklist<T>::Iterator it;
			for (it = ptr->begin(); it != ptr->end(); ++it)
				if ((*it) == tdata) return &(*it);
			ptr->push_back(tdata);
			it = ptr->end();
			return &(*(--it));
		}

		T* find(const T& tdata)
		{
			int id = tdata.hash(P);
			linklist<T>* ptr = &data[id];
			linklist<T>::Iterator it;
			for (it = ptr->begin(); it != ptr->end(); ++it)
				if ((*it) == tdata) return &(*it);
			return NULL;
		}

	};
}

#endif // !HASH_H
