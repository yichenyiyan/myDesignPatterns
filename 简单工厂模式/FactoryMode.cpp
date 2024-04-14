#include<iostream>
using namespace std;


//�򵥹���ģʽ��Simple Factory Pattern��: 
// ͨ��һ�������������𴴽����ж����ʵ�����ͻ���ͨ�����ݲ�ͬ�Ĳ���������������ȡ��ͬ�Ķ���ʵ����


enum class OSNAME {
	Uinx = 0,
	Linux,
	Windows,
	MacOS
};


//���˵��Բ���ϵͳ�������ࣩ
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


//������������
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