



#include<iostream>
using namespace std;


//工厂方法模式（Factory Method Pattern） : 
// 定义一个创建对象的接口，但是让子类来决定实例化的类是哪一个。每个具体工厂类负责创建特定类型的对象。

//省略构造函数...
class OS {
public:
	virtual void describle() = 0;
};

class Linux :public OS {
public:
	void describle() {
		std::cout << "Linux" << std::endl;
	}
};

class Windows :public OS {
public:
	void describle() {
		std::cout << "Windows" << std::endl;
	}
};

class MacOS :public OS {
public:
	void describle() {
		std::cout << "MacOS" << std::endl;
	}
};

class DriveFactory {
public:
	virtual OS* produceDriveFor() = 0;
};


//假设NDIVIA专门给Windows写驱动（实际上并不是）
class NDIVIA :public DriveFactory {
public:
	OS* produceDriveFor() {
		return (new Windows());
	}
};

class Intel :public DriveFactory {
public:
	OS* produceDriveFor() {
		return (new Linux());
	}
};

class TSMC :public DriveFactory {
public:
	OS* produceDriveFor() {
		return (new MacOS());
	}
};

int main()
{
	DriveFactory* factory1 = new Intel();
	OS* os1 = factory1->produceDriveFor();
	os1->describle();

	delete os1;
	delete factory1;

	return 0;
}