#ifndef INTERFACE_H
#define INTERFACE_H

/**
@brief Interface\n
@file interface.h
@author ShadowIterator
@email ShadowIterator@hotmail.com
@version 0.1
@date 2017.12.24
*/

#include"si_global.h"
#include"sistring.h"
namespace SI
{
	void extractInfo(char* infilename, std::ofstream& fout);	///<Ҫ��Ľӿ�
	void initDictionary();	///<Ҫ��Ľӿ�
	SIStringList divideWords(SIString contents);	///<Ҫ��Ľӿ�
	void destroyDictionary();	///<Ҫ��Ľӿ�
}
#endif //INTERFACE_H