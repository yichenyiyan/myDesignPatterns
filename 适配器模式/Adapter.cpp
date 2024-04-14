/******************************
*  Github:å¤§å°å§çš„å°è¿·å¼Ÿ             *
*       yichenyan  QAQ        *
* ç¼–ç¨‹å­¦ä¹ åº”è¯¥æ˜¯ç®€å•ä¸”æœ‰è¶£çš„  *
*******************************/



#include<iostream>
#include<string>
#include<cassert>
#include<algorithm>


//Éè¼ÆÄ£Ê½£ºÊÊÅäÆ÷Ä£Ê½

class Target {
public:
	virtual ~Target() = default;
	virtual std::string Request() = 0;
};



//±»ÊÊÅäÕß
class Adaptee {
public:
	std::string specificRequest() {
		return static_cast <std::string>(".eetpadA eht fo roivaheb laicepS");
	}
};

//ÊÊÅäÆ÷
class Adapter :public Target{
private:
	Adaptee* adapter;
public:
	Adapter(Adaptee* adapter) :adapter(adapter) {

	}
	std::string Request() {
		std::string targetStr = adapter->specificRequest();
		std::reverse(targetStr.begin(), targetStr.end());
		return "after adapter translate the string is: " + targetStr;
	}

};


int main()
{
	Adaptee* adaptee = new Adaptee();
	assert(adaptee != nullptr);
	std::cout << "before translate the adaptee's str is:";
	std::cout << adaptee->specificRequest() << std::endl;

	Adapter* adapter = new Adapter(adaptee);
	std::cout << "after translate the adaptee's str is:";
	std::cout << adapter->Request() << std::endl;

	delete adaptee;
	delete adapter;

	return 0;
}