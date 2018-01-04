#ifndef INTERFACE_H
#define INTERFACE_H

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