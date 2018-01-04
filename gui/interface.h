#ifndef INTERFACE_H
#define INTERFACE_H

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