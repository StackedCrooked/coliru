#include <iostream>

class Base
{
       public:
      	Base(){ std::cout<<"Constructing Base\n";}
      	
     // this is a destructor:
	
	 ~ Base(){ std::cout<<"Destroying Base\n";}
};

class Derive: public Base
{
        public:
       	Derive(){ std::cout<<"Constructing Derive\n";}
       	
       	virtual ~Derive(){ std::cout<<"Destroying Derive\n";}
 };
 class Derive2: public Derive
{
        public:
           Derive2(){ std::cout<<"Constructing Derive2\n";}
       	
       	~Derive2(){ std::cout<<"Destroying Derive2\n";}
 };

 int main()
{
    	Base *basePtr = new Derive2();
        
        delete basePtr;
}