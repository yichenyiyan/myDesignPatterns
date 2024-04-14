



#include<iostream>
using namespace std;


//��������ģʽ��Factory Method Pattern�� : 
// ����һ����������Ľӿڣ�����������������ʵ������������һ����ÿ�����幤���ฺ�𴴽��ض����͵Ķ���

//ʡ�Թ��캯��...
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


//����NDIVIAר�Ÿ�Windowsд������ʵ���ϲ����ǣ�
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