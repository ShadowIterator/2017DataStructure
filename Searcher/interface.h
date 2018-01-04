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
	void extractInfo(char* infilename, std::ofstream& fout);	///<要求的接口
	void initDictionary();	///<要求的接口
	SIStringList divideWords(SIString contents);	///<要求的接口
	void destroyDictionary();	///<要求的接口
}
#endif //INTERFACE_H