#include <iostream>
#include <memory>
#include <vector>

class Foo
{

public:

    Foo() {

	}

};

class Child
{

public:

	Child(std::weak_ptr<Foo> parent) {
    	m_parent = parent;
	}

private:

	std::weak_ptr<Foo> m_parent;

};

void deleteFoo(Foo* arg) {
	std::cout << "Deleting Foo" << std::endl;
	delete arg;
}

void deleteChild(Child* arg) {
	std::cout << "Deleting Child" << std::endl;
	delete arg;
}


int main(int argc, char** argv)
{
	//{ //Scope

		std::shared_ptr<Foo> foo = std::shared_ptr<Foo>(new Foo(), deleteFoo);

		std::vector<std::shared_ptr<Child>> children;
		for (int i = 0; i < 10; ++i) {
			children.push_back(std::shared_ptr<Child>(new Child(foo), deleteChild));
		}

	//}
    
    foo.reset();

	std::cout << "Finished" << std::endl;
	getchar();

	return EXIT_SUCCESS;
}