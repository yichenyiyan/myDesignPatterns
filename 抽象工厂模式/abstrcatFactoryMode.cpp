



#include<iostream>
using namespace std;


//抽象工厂模式（Abstract Factory Pattern） : 
// 提供一个接口，用于创建相关或依赖对象的家族，而不需要指定具体的类。
// 具体的工厂类负责实现这个接口来创建一系列相关的对象。


class OS {
public:
	virtual void describle() = 0;
};

class Linux :public OS{
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


class OSpro {
public:
	virtual void describle() = 0;
};

class Linux1 :public OSpro {
public:
	void describle() {
		std::cout << "Linux 1.0" << std::endl;
	}
};

class Windows1 :public OSpro {
public:
	void describle() {
		std::cout << "Windows 1.0" << std::endl;
	}
};

class MacOS1 :public OSpro {
public:
	void describle() {
		std::cout << "MacOS 1.0" << std::endl;
	}
};

class DriveFactory {
public:
	virtual OS* produceDriveFor() = 0;

	virtual OSpro* newproduceDriveFor() = 0;
};

class NDIVIA :public DriveFactory {
public:
	OS* produceDriveFor() {
		return (new Windows());
	}
	OSpro* newproduceDriveFor() {
		return (new Windows1());
	}
};

class Intel :public DriveFactory {
public:
	OS* produceDriveFor() {
		return (new Linux());
	}
	OSpro* newproduceDriveFor() {
		return (new Linux1());
	}
};

class TSMC :public DriveFactory {
public:
	OS* produceDriveFor() {
		return (new MacOS());
	}
	OSpro* newproduceDriveFor() {
		return (new MacOS1());
	}
};


int main()
{
	DriveFactory* factory = new NDIVIA();
	OS* os1 = factory->produceDriveFor();
	OSpro* os1pro = factory->newproduceDriveFor();

	os1->describle();
	os1pro->describle();


	delete os1;
	delete os1pro;
	delete factory;



	return 0;
}