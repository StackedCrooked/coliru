#include <iostream>
#include <vector>

struct Animal{
    virtual void sayHello() = 0;
};

struct Dog   : Animal { virtual void sayHello(){ std::cout << "Woof\n"; } };
struct Cat   : Animal { virtual void sayHello(){ std::cout << "Miau\n"; } };
struct Fish  : Animal { virtual void sayHello(){ std::cout << "Blub\n"; } };
struct Bird  : Animal { virtual void sayHello(){ std::cout << "Chirp\n"; } };
struct Rabbid: Animal { virtual void sayHello(){ std::cout << "Meeep\n"; } };

int main(){
    std::vector<Animal*> animals;
	animals.push_back(new Dog());
	animals.push_back(new Cat());
	animals.push_back(new Fish());
	animals.push_back(new Bird());
	animals.push_back(new Rabbid());

	for(std::vector<Animal*>::iterator it = animals.begin(); it != animals.end(); ++it){
		(*it)->sayHello();
		delete *it;
	}
}