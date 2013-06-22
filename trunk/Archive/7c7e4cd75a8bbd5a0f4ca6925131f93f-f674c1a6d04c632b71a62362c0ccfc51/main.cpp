#include <memory>
#include <iostream>

 
class foo
{
    public:
    void print() {std::cout << "foo::print" << std::endl;}
};
   
int main()
{
    std::auto_ptr<foo> ap1(new foo);
    ap1->print();
    std::cout << "ap1 pointer: " << ap1.get() << std::endl;
     
    std::shared_ptr<foo> sp1((std::auto_ptr<foo>)ap1);
    sp1->print();
    
    std::cout << "ap1 pointer: " << ap1.get() << std::endl;
    std::cout << "sp1 pointer: " << sp1.get() << std::endl;

    return 0;
}
 