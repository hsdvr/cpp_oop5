#include <iostream>
using namespace std;

class Animal {
private:
	string name;
	int age;
public:
	void sound() {
		cout << "Some Animal sound\n";
	}
	virtual void eat() {
		cout << "Some Animal is eating smth\n";
	}
};

class Cat : public Animal {
private:
	
public:
	void sound() {
		cout << "Mew-mew\n";
	}
	void eat() override {
		cout << "Cat is eating Kitiket\n";
	}
};

class Dog :public Animal {
private:

public:
	void sound() {
		cout << "Wow-wow\n";
	}
	void eat() override {
		cout << "Dog is eating Pedigree\n";
	}
};



int main() {
	setlocale(LC_ALL, "RU");
	Cat* cat = new Cat();
	Dog* dog = new Dog();
	const int num_of_pets = 2;
	Animal* my_pets[2];
	my_pets[0] = cat;//new Cat();
	my_pets[1] = dog;
	cout << "Вызов перекрываемых методов объектов, находящихся в переменных-указателях класса-предка\n";
	my_pets[0]->sound();
	my_pets[1]->sound();
	cout << "Вызов перекрываемых методов объектов, находящихся в переменных-указателях своего класса\n";
	cat->sound();
	dog->sound();

	cout << "Вызов виртуального метода объектов\n";
	cat->eat();
	my_pets[1]->eat();
	cout << "Вызов виртуального метода непосредственно у объекта базового класса\n"; 
	Animal* anml = new Animal();
	anml->eat();
}