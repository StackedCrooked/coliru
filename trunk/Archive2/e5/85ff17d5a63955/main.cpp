#include <vector>
#include <string>
#include <iostream>
 
class A {
    public:
        virtual ~A() {}
        virtual std::vector<int> Choose(double* total) const = 0;
        
        virtual std::vector<int> Choose() const  { 
            std::cout << "Choose without parameter" << std::endl;
            return Choose(nullptr);
        }
};

class B : public A {
    public:
        virtual std::vector<int> Choose(double* total) const {
            if (total) {
                *total = 42.0;
            }
            
            return std::vector<int>();
        }
};

 
int main()
{
    double total;
    B b;    
    b.Choose(&total);    
    b.Choose();
    std::cout << total << std::endl;
}