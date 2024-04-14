#include<iostream>
#include<string>
#include<unordered_map>

//原型设计模式


enum TYPE {
	PROTOTYPE1 = 0,
	PROTOTYPE2
};


class Prototype {
protected:
	std::string prototype_name;
	float prototype_field;
public:
	Prototype() {}
	Prototype(std::string prototype_name):prototype_name(prototype_name){}

	virtual ~Prototype(){}
	virtual Prototype* Clone() const = 0;
	virtual void Method(float prototype_field) {
		this->prototype_field = prototype_field;
		std::cout << "Call Method from " << prototype_name << " with field : " << prototype_field << std::endl;
	}
};

class ConcretePrototype1 :public Prototype {
private:
	float concrete_prototype_field1;
public:
	ConcretePrototype1(std::string prototype_name, float concrete_prototype_field) 
		:Prototype(prototype_name), concrete_prototype_field1(concrete_prototype_field){}

	//*this 表示当前对象的引用。在C++中，
	// this 是一个指向当前对象的指针，在成员函数中使用它可以访问当前对象的成员变量和成员函数。
	// 使用 *this 则是将指针解引用，得到当前对象本身。
	Prototype* Clone() const override{
		return new ConcretePrototype1(*this);
	}
};


class ConcretePrototype2 :public Prototype {
private:
	float concrete_prototype_field2;
public:
	ConcretePrototype2(std::string prototype_name, float concrete_prototype_field)
		:Prototype(prototype_name), concrete_prototype_field2(concrete_prototype_field) {}

	Prototype* Clone() const override {
		return new ConcretePrototype2(*this);
	}
};

class PrototypeFactory {
private:
	//这是一个哈希函数对象，用于计算键的哈希值。
	// 在这个例子中，键的类型是 int，所以使用了 std::hash<int>。
	// 哈希函数负责将键转换为其对应的哈希值，以便在 unordered_map 中快速查找对应的值。
	std::unordered_map<TYPE, Prototype*, std::hash<int>> prototypes;

public:
	PrototypeFactory() {
		prototypes[TYPE::PROTOTYPE1] = new ConcretePrototype1("PROTOTYPE1 ", 50.f);
		prototypes[TYPE::PROTOTYPE2] = new ConcretePrototype2("PROTOTYPE2 ", 60.f);
	}

	~PrototypeFactory() {
		delete prototypes[TYPE::PROTOTYPE1];
		delete prototypes[TYPE::PROTOTYPE2];
	}

	
	Prototype* CreatePrototype(TYPE type) {
		return prototypes[type]->Clone();
	}
};


void Client(PrototypeFactory& prototype_factory) 
{
	std::cout << "Let's create a Prototype 1\n";

	Prototype* prototype = prototype_factory.CreatePrototype(TYPE::PROTOTYPE1);
	prototype->Method(90);
	delete prototype;

	std::cout << "\n";

	std::cout << "Let's create a Prototype 2 \n";

	prototype = prototype_factory.CreatePrototype(TYPE::PROTOTYPE2);
	prototype->Method(10);

	delete prototype;
}

int main() 
{
	PrototypeFactory* prototype_factory = new PrototypeFactory();
	Client(*prototype_factory);
	delete prototype_factory;

	return 0;
}