#include <iostream>
#include <functional>

struct Something {
    Something() {
        
    }
    
    void setThing(
        std::function<int()> a,
    	std::function<int()> b,
		std::function<int()> c
    ) {
        this->a = a;
        this->b = b;
        this->c = c;
        
    }
    
    int run() {
        return this->a() + this->b() + this->c();   
    };
    
    private:
        std::function<int()> a;
		std::function<int()> b;
		std::function<int()> c;
};

int main()
{
    
   Something myThing;
   
   myThing.setThing(
        [&]() {
        	return 1;
        },
        [&]() {
            return 2;
        },
        [&]() {
            return 3;
        }
    );
    
    std::cout << myThing.run();
}