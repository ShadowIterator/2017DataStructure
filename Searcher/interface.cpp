#include"si_global.h"
#include"linklist.h"
#include"sistring.h"
#include"segmentationer.h"


namespace SI
{	
	using std::ofstream;
	using std::ifstream;
	using std::string;
	using std::endl;
	using std::cout;

	void initDictionary()
	{
		cout << "allocing buffer" << endl;
	//	SelfClosedLabelChecker::allocBuff(SelfClosedLabelChecker::BUFF_SIZE);
		Segmentationer::allocBuff(Segmentationer::BUFF_SIZE);
	//	cout << "loading encoding comparsion list" << endl;
	//	SIString::init("UnicodeToGBK.csv");
		cout << "loading html label infomation" << endl;
	//	SelfClosedLabelChecker::init("SelfClosedLabel.list");
		cout << "loading dictionary" << endl;
		Segmentationer::loadDic("dictionary.dic");

	}
	
	void destroyDictionary()
	{
//		SelfClosedLabelChecker::destroyBuff();
		Segmentationer::destroyBuff();
	}

	SIStringList divideWords(SIString contents)
	{
		return Segmentationer::doSegmentation(contents);
	}
}
