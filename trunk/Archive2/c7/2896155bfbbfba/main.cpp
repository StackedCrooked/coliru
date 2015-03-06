#include <iostream>


struct Something {
    Something() {
        
    }
    
    template<typename Func, typename Func2, typename Func3>
    void setThing(
        Func a,
    	Func2 b,
		Func3 c
    ) {
        this->a = a;
        this->b = b;
        this->c = c;
        
    }
    
    void run() {
        return this->a() + this->b() + this->c();   
    }
    
    private:
        Func a;
		Func2 b;
		Func3 c;
};

int main()
{
    
   Something myThing();
   
   myThing.run(
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
}