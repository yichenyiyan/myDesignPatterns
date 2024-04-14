



#include<mutex>
#include<iostream>
using namespace std;

//����ģʽ

//����ģʽ���Է�Ϊ ����ʽ �� ����ʽ ������֮����������ڴ���ʵ����ʱ�䲻ͬ��

/*
*����ʽ
* 
*ϵͳ�����У�ʵ���������ڣ�ֻ�е���Ҫʹ�ø�ʵ��ʱ���Ż�ȥ������ʹ��ʵ�������ַ�ʽҪ�����̰߳�ȫ��

*����ʽ
* 
*ϵͳһ���У��ͳ�ʼ������ʵ��������Ҫʱ��ֱ�ӵ��ü��ɡ����߸��˾������ַ�ʽ��������̰߳�ȫ��
*/


//����ʽ��������


class single {
public:

	//��ȡ��������ָ��
	static single* getSingle();

	//�ͷŵ�ʵ��
	static void deleteSingle();

	//�������ܺ�������������ֻ�����ӡ����ʵ���ĵ�ַ��
	void func();
private:
	single();
	~single();
	single(const single& s);
	const single& operator=(const single& s);
private:
	//Ψһʵ�����Ķ���ָ��
	static single* pSingle;
	//��
	static std::mutex mtx;
};


//��ʼ����̬��Ա����
single* single::pSingle = nullptr;
std::mutex single::mtx;

single*
single::getSingle()
{
	if (pSingle == nullptr) {
		{
			std::unique_lock<std::mutex> lck(mtx);
			//���߱�������Ҫ�Ա��Ϊ volatile �ı��������Ż�
			volatile auto temp = new (std::nothrow) single();//std::nothrow���ڴ����ʧ��ʱ���׳��쳣
			pSingle = temp;
		}
	}

	return pSingle;
}

void 
single::deleteSingle()
{
	std::unique_lock<std::mutex> lck(mtx);
	if (pSingle != nullptr) {

		delete pSingle;
		pSingle = nullptr;
	}
}

void 
single::func()
{
	std::cout << "����ʵ��������ĵ�ַΪ��" << pSingle << std::endl;
}


single::single()
{
	std::cout << "single ���캯��" << std::endl;
}

single::~single()
{
	std::cout << "single ��������" << std::endl;
}


void testFunc1()
{
	auto ptr_single = single::getSingle();
	std::cout << "ptr_single address:" << ptr_single << std::endl;
	ptr_single->func();
	ptr_single->deleteSingle();
}


int main(void)
{
	testFunc1();

	return 0;
}