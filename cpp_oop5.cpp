#include <iostream>
using namespace std;

class Animal {
private:
	string name;
	int age;
public:
	// конструкторы
	Animal() : name("Undefined"), age(0) {};
	Animal(string _name, int _age): name(_name),age(_age) {};
	Animal(Animal& an) {
		name = an.getName();
		age = an.getAge();
	}
	virtual ~Animal() {
		cout << "~Animal\n";
	}

	string getName() {
		return name;
	}
	int getAge() {
		return age;
	}
	void sound() {
		cout << "Some Animal sound\n";
	}
	virtual void eat() {
		cout << "Some Animal is eating smth\n";
	}

	virtual string classname() {
		return "Animal";
	}

	virtual bool isA(const string& classname) {
		return (classname == "Animal");

	}

	void say() {
		sound();// невиртуальный
	}
	void sayClassname() {
		cout << classname() << endl; // виртуальный
	}
};

class Cat : public Animal {
private:
	
public:
	// конструкторы
	Cat() {};
	Cat(string _name, int _age) : Animal(_name, _age) {};
	Cat(Cat& c) : Animal(c) {}
	~Cat() {
		cout << "~Cat\n";
	}
	void sound() {
		cout << "Mew-mew\n";
	}
	/*void giveSpace() {

	}*/
	/*void eat() override {
		cout << "Cat is eating Kitiket\n";
	}*/

	void catchMouse() {
		cout << "Cat catch mouse\n";
	}
	string classname() {
		return "Cat";
	}

	bool isA(const string& classname) {
		return (classname == "Cat" || Animal::isA(classname));

	}
};

class Dog :public Animal {
private:

public:
	// конструкторы
	Dog() {}
	Dog(string _name, int _age) : Animal(_name, _age) {}
	Dog(Dog& d) : Animal(d) {}
	~Dog() {
		cout << "~Dog\n";
	}
	void sound() {
		cout << "Wow-wow\n";
	}
	void eat() override {
		cout << "Dog is eating Pedigree\n";
	}
	void guardHouse() {
		cout << "Dog guard house\n";
	}

	string classname() {
		return "Dog";
	}

	bool isA(const string& classname) {
		return (classname == "Dog" || Animal::isA(classname));

	}

};

class PersianCat: public Cat {
private:
public:
	// конструкторы
	PersianCat() {}
	PersianCat(string _name, int _age) : Cat(_name, _age) {}
	PersianCat(PersianCat& pc) : Cat(pc) {}
	~PersianCat() { cout << "~PersianCat\n"; }

	string classname() {
		return "PersianCat";
	}

	bool isA(const string& classname) {
		return (classname == "PersianCat" || Cat::isA(classname));

	}
};


int main() {
	setlocale(LC_ALL, "RU");
	Cat* cat = new Cat();
	Dog* dog = new Dog();
	const int NUM_OF_PETS = 3;
	Animal* my_pets[NUM_OF_PETS];
	my_pets[0] = cat;
	my_pets[1] = dog;
	my_pets[2] = new PersianCat();
	cout << "Вызов перекрываемых методов объектов, находящихся в переменных-указателях класса-предка\n";
	my_pets[0]->sound();
	my_pets[1]->sound();
	cout << "Вызов перекрываемых методов объектов, находящихся в переменных-указателях своего класса\n";
	cat->sound();
	dog->sound();

	cout << "Вызов виртуального метода объектов\n";
	cat->eat();// у класса Cat не перекрыт метод eat()
	dog->eat();//метод перекрыт
	my_pets[1]->eat();//метод перекрыт, объект в переменной-указ базового класса
	
	cout << "Виртуальный деструктор\n";
	cout << "delete cat:\n";
	delete cat;// сначала вызовется деструктор самого объекта, далее всех его предков
	cat = new Cat();
	my_pets[0] = cat;

	cout << "\nПриведение типов\n";
	cout << "Небезопасное приведение типов с проверкой classname()\n";
	for (int i = 0; i < NUM_OF_PETS; i++)
		if (my_pets[i]->classname() == "Cat") {
			cout << my_pets[i]->classname() << ": ";
			static_cast<Cat*>(my_pets[i])->catchMouse();
		}
	/// <summary>
	/// возникла проблема: для потомков Cat не будет вызван метод catchMouse()
	/// </summary>
	/// 
	
	cout << "Небезопасное приведение типов с проверкой isA()\n";
	for (int i = 0; i < NUM_OF_PETS; i++)
		if (my_pets[i]->isA("Cat")) {
			cout << my_pets[i]->classname() << ": ";
			static_cast<Cat*>(my_pets[i])->catchMouse();
		}
	
	cout << "Безопасное приведение типов\n";
	for (int i = 0; i < NUM_OF_PETS; i++) {
		Cat* cat = dynamic_cast<Cat*>(my_pets[i]);
		if (cat != nullptr) {
			cout << my_pets[i]->classname() << ": ";
			cat->catchMouse();
		}
	}
	cout << endl;
	
	cout << "\nВ методе say() базового класса вызывается невиртуальный метод sound(), который переопределен в классе-потомке\n";
	cat->say();
	cout << "\nВ методе sayClassname() базового класса вызывается виртуальный метод classname(), который переопределен в классе-потомке\n";
	cat->sayClassname();

	

}