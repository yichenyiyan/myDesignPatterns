



#include<mutex>
#include<iostream>
using namespace std;

//单例模式

//单例模式可以分为 懒汉式 和 饿汉式 ，两者之间的区别在于创建实例的时间不同。

/*
*懒汉式
* 
*系统运行中，实例并不存在，只有当需要使用该实例时，才会去创建并使用实例。这种方式要考虑线程安全。

*饿汉式
* 
*系统一运行，就初始化创建实例，当需要时，直接调用即可。作者个人觉得这种方式本身就是线程安全。
*/


//懒汉式（加锁）


class single {
public:

	//获取单例对象指针
	static single* getSingle();

	//释放单实例
	static void deleteSingle();

	//其他功能函数（本案例中只输出打印单例实例的地址）
	void func();
private:
	single();
	~single();
	single(const single& s);
	const single& operator=(const single& s);
private:
	//唯一实例化的对象指针
	static single* pSingle;
	//锁
	static std::mutex mtx;
};


//初始化静态成员变量
single* single::pSingle = nullptr;
std::mutex single::mtx;

single*
single::getSingle()
{
	if (pSingle == nullptr) {
		{
			std::unique_lock<std::mutex> lck(mtx);
			//告诉编译器不要对标记为 volatile 的变量进行优化
			volatile auto temp = new (std::nothrow) single();//std::nothrow在内存分配失败时不抛出异常
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
	std::cout << "单例实例化对象的地址为：" << pSingle << std::endl;
}


single::single()
{
	std::cout << "single 构造函数" << std::endl;
}

single::~single()
{
	std::cout << "single 析构函数" << std::endl;
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