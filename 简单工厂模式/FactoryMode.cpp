#include<iostream>
using namespace std;


//简单工厂模式（Simple Factory Pattern）: 
// 通过一个工厂类来负责创建所有对象的实例，客户端通过传递不同的参数给工厂类来获取不同的对象实例。


enum class OSNAME {
	Uinx = 0,
	Linux,
	Windows,
	MacOS
};


//个人电脑操作系统（抽象类）
class PcOS {
public:
	virtual void describle() = 0;
};


class Uinx :public PcOS {
public:
	void describle() {
		std::cout << "OS: Uinx" << std::endl;
	}
	Uinx(){}
	~Uinx(){}
};


class Linux :public PcOS{
public:
	void describle() {
		std::cout << "OS: Linux" << std::endl;
	}
	Linux(){}
	~Linux(){}
};


class Windows :public PcOS {
public:
	void describle() {
		std::cout << "OS: Windows" << std::endl;
	}
	Windows(){}
	~Windows(){}
};


class MacOS :public PcOS {
public:
	void describle() {
		std::cout << "OS: MacOS" << std::endl;
	}
	MacOS(){}
	~MacOS(){}
};


//驱动生产厂商
class  driveFactory {
public:
	PcOS* writeDriveForPC(OSNAME name) {
		switch (name) {
		case OSNAME::Uinx:
			return (new (std::nothrow)Uinx());
			break;
		case OSNAME::Linux:
			return (new (std::nothrow)Linux());
			break;
		case OSNAME::Windows:
			return (new (std::nothrow)Windows());
			break;
		case OSNAME::MacOS:
			return (new (std::nothrow)MacOS());
			break;
		default:
			return nullptr;
			break;
		}
	}
	driveFactory(){}
	~driveFactory(){}
};

int main() { return 0; }