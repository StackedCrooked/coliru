#include <string>
#include <iostream>

class A
{
    protected:
    
    std::string m_str;
    
    
    public:
    
    A()
     : m_str("hello")
     {}
     
    ~A()
    {}
};

class B : public A
{
    public:
    
    const std::string* GetMember() const { return &m_str; }
};

void foo(A const *pa)
{
  B const *pb(reinterpret_cast<B const *>(pa));
  
  std::cout << *pb->GetMember() << std::endl;
}


int main(int argc, char* argv[])
{

    A a;
    
    foo(&a);

	return 0;
}
