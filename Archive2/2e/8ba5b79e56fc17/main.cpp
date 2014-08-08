#include <iostream>
//#include <memory>

struct f1
{
    f1() : m_a(1) {};
    void function1()
    {
        std::cout << "function f1 " << m_a << std::endl;
    }
    
    int m_a;
};

struct f2 : f1
{
    f2() :f1()
    {
        m_ptr_f1 = this;
        m_b = 2;
    };
    void function2()
    {
        std::cout << "fuction f2 " << m_b << std::endl;
        m_ptr_f1->function1();
    }
    
    int m_b;
    f1 *m_ptr_f1;
};

struct f3 : f2
{
    f3() : f2()
    {
        m_ptr_f2 = this;
        m_c = 3;
    };
    void function3()
    {
        std::cout << "fuction f3 " << m_c << std::endl;
        m_ptr_f2->function2 ();
    }
    
    int m_c;
    f2 *m_ptr_f2;
};

int main()
{
    f3* ptr3 = new f3;
  ptr3->function3();
  delete ptr3;
  std::cout << "end of program" << std::endl;
  //std::cin.get();
    return 0;
}