/******************************
*  Github:大小姐的小迷弟             *
*       yichenyan  QAQ        *
* 编程学习应该是简单且有趣的  *
*******************************/



#include<iostream>
#include<string>
#include<cassert>
#include<algorithm>


//���ģʽ��������ģʽ

class Target {
public:
	virtual ~Target() = default;
	virtual std::string Request() = 0;
};



//��������
class Adaptee {
public:
	std::string specificRequest() {
		return static_cast <std::string>(".eetpadA eht fo roivaheb laicepS");
	}
};

//������
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