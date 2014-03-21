#include <iostream>
#include <vector>

class Foo
{
    private:
        std::vector<int> I;
        
    public:
		Foo() {std::cout<<"Constructed\n";}
		Foo(const Foo &other) : I(other.I) {std::cout<<"Copied\n";}
		//Foo(Foo &&other) : I(other.I) {std::cout<<"Moved\n";}
		~Foo() {std::cout<<"Destructed\n";}
		
		Foo& operator = (const Foo &other) {std::cout<<"Assigned\n"; I = other.I; return *this;}
};

int main()
{
	std::vector<Foo> v(5);
    
    std::cout<<"Elements constructed\n\n\n";
	v.erase(v.begin());
	std::cout<<"Erased first element\n\n\n";
	
	
	return 0;
}