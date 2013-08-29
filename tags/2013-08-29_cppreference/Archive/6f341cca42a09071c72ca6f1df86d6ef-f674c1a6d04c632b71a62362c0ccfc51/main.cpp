#include <iostream>
#include <vector>

class Base {
protected:
   virtual ~Base() {} //if you have virtual functions, ALWAYS have a virtual destructor in the base class
public:
   virtual void execute() = 0;
   
   static std::vector<Base*>& registrationList() { //note this staic is unrelated to static on next line
        static std::vector<Base*> registrationList; //note this staic is unrelated to static on previous line
        return registrationList;
   }
};
template<class T>
struct registration {
    T instance;
    registration() {Base::registrationList().push_back(&instance);}
};




class ImplementationOne: public Base {
public:
    void execute(){std::cout << "Implementation One" << std::endl;}   
};
registration<ImplementationOne> one;


class ImplementationTwo: public Base {
public:
     void execute(){std::cout << "Implementation Two" << std::endl;}   
};
registration<ImplementationTwo> two;


int main(int argc, const char * argv[]){
    std::cout << "Registration List size: " << Base::registrationList().size() << std::endl;
    for(auto it = Base::registrationList().begin() ; it != Base::registrationList().end() ; ++it)
        (*it)->execute();
    return 0;
}