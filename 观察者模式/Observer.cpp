#include<iostream>
#include<list>
#include<string>



class IObserver {
public:
	virtual ~IObserver() {};
	virtual void Update(const std::string& message_from_subject) = 0;
};


class ISubject {
public:
	virtual ~ISubject() {};
	virtual void Attach(IObserver* observer) = 0;
	virtual void Detach(IObserver* observer) = 0;
	virtual void Notify() = 0;
};

class Subject :public ISubject {
private:
	std::string message;
	std::list<IObserver*> observers;
public:
	virtual ~Subject() {
		std::cout << "Goodbye. I was the Subject." << std::endl;
	}

	//如果派生类在虚函数声明时使用了override描述符，那么该函数必须重载其基类中的同名函数，否则代码将无法通过编译。
	void Attach(IObserver* observer) override {//添加观察者
		observers.push_back(observer);
	}

	void Detach(IObserver* observer) override {//移除观察者
		observers.remove(observer);
	}

	void Notify() override {
		auto iterator = observers.begin();
		HowManyObserver();
		while (iterator != observers.end()) {
			(*iterator)->Update(message);
			++iterator;
		}
	}


	void CreateMessage(std::string msg = "Empty"){
		this->message = msg;
		this->Notify();
	}

	void HowManyObserver() {
		std::cout << "There are " << observers.size() << " observers" << std::endl;
	}
};

class Observer :public IObserver {
private:
	std::string msg;
	Subject& subject;
	static int static_number; //观察者总数
	int number;
public:
	Observer(Subject& subject) :subject(subject) {
		this->subject.Attach(this);
		std::cout << "Hi, I'm the No.\"" << ++Observer::static_number << "\" Observer" << std::endl;
		this->number = Observer::static_number;
	}

	virtual ~Observer() {
		std::cout << "Goodbye. I was the No.\"" << this->number << "\" Observer" << std::endl;
	}

	void Update(const std::string& msg) override {
		this->msg = msg;
		PrintInfo();
	}

	void RemoveMeFromTheList() {//取消关注该subject（频道）
		subject.Detach(this);
		std::cout << "Observer \"" << this->number << "\" removed from the observers list." << std::endl;
	}

	void PrintInfo() {
		std::cout << "Observer \"" << this->number << "\" recv a new message: " << this->msg << std::endl;
	}

};

int Observer::static_number = 0;

void testFunc1()
{
	Subject* subject = new Subject;
	Observer* observer1 = new Observer(*subject);
	Observer* observer2 = new Observer(*subject);
	Observer* observer3 = new Observer(*subject);
	Observer* observer4 = nullptr;
	Observer* observer5 = nullptr;

	subject->CreateMessage("iPhone 20!!!");
	observer3->RemoveMeFromTheList();

	subject->CreateMessage("iPhone 20 pro Max!!!");
	observer4 = new Observer(*subject);

	observer2->RemoveMeFromTheList();
	observer5 = new Observer(*subject);

	subject->CreateMessage("iPad 88!!!");
	observer5->RemoveMeFromTheList();

	observer4->RemoveMeFromTheList();
	observer1->RemoveMeFromTheList();

	delete observer5;
	delete observer4;
	delete observer3;
	delete observer2;
	delete observer1;
	delete subject;
}


int main()
{
	testFunc1();

	return 0;
}