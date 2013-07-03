#include <iostream>
#include <vector>

class Base {
protected:
   Base(){registrationList().push_back(this);}
   virtual ~Base() {} //if you have virtual functions, ALWAYS have a virtual destructor in the base class
public:
   virtual void execute() = 0;
   
   static std::vector<Base*>& registrationList() { //note this staic is unrelated to static on next line
        static std::vector<Base*> registrationList; //note this staic is unrelated to static on previous line
        return registrationList;
   }
};

class ImplementationOne: public Base {
public:
    void execute(){std::cout << "Implementation One" << std::endl;}   
};

class ImplementationTwo: public Base {
public:
     void execute(){std::cout << "Implementation Two" << std::endl;}   
};


ImplementationOne static_impl_one; //these are the actual instances that are registered.
ImplementationTwo static_impl_two;

int main(int argc, const char * argv[]){
    std::cout << "Registration List size: " << Base::registrationList().size() << std::endl;
    for(auto it = Base::registrationList().begin() ; it != Base::registrationList().end() ; ++it)
        (*it)->execute();
    return 0;
}