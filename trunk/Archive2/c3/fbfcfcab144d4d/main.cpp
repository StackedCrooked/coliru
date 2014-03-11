#include <iostream>
#include <vector>
#include <boost/shared_ptr.hpp>

class Interface{
    public:
    typedef boost::shared_ptr<Interface> ptr;
    virtual ~Interface(){}
};
class Line : public Interface{};
class Circle : public Interface{
    public:
        double center(){
            return 5.;
        }
};

std::vector<Interface::ptr> vec;

int main(){
    Interface::ptr ptrL(new Line());
    vec.push_back(ptrL);
    Interface::ptr ptrC(new Circle());
    vec.push_back(ptrC);
    
    try{
        Circle& c= dynamic_cast<Circle&>( *(vec[0]) );
        std::cout << c.center() << std::endl;
    }
    catch(std::bad_cast&){}
    
    return 0;
}
