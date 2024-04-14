#include<iostream>
#include<string>
#include<unordered_map>

//ԭ�����ģʽ


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

	//*this ��ʾ��ǰ��������á���C++�У�
	// this ��һ��ָ��ǰ�����ָ�룬�ڳ�Ա������ʹ�������Է��ʵ�ǰ����ĳ�Ա�����ͳ�Ա������
	// ʹ�� *this ���ǽ�ָ������ã��õ���ǰ������
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
	//����һ����ϣ�����������ڼ�����Ĺ�ϣֵ��
	// ����������У����������� int������ʹ���� std::hash<int>��
	// ��ϣ�������𽫼�ת��Ϊ���Ӧ�Ĺ�ϣֵ���Ա��� unordered_map �п��ٲ��Ҷ�Ӧ��ֵ��
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