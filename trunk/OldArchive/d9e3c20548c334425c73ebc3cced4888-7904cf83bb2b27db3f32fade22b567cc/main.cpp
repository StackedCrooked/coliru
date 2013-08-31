#include <iostream>
#include <string>
#include <vector>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}


class B1
{
private:
    virtual void f_priv(){ std::cout << "B1:priv" << std::endl; }
    
public:
    virtual void f_publ(){ std::cout << "B1:f_publ" << std::endl; }
};


class B2 : public B1
{
public:
    virtual void f_priv(){ std::cout << "B2:priv" << std::endl; }
    
private:
    virtual void f_publ(){ std::cout << "B2:f_publ" << std::endl; }
};


class D : public B2
{
private:
    virtual void f_priv(){ std::cout << "D:priv" << std::endl; }
    
public:
    virtual void f_publ(){ std::cout << "D:f_publ" << std::endl; }
};


int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
    
    D d;
    B1 b1;
    B2 b2;
    
    B1 &b = b2;
    b.f_publ(); // works, is private in B2
    //b.f_priv();  // does not work, is brivate in B1
    
    B1 &bb = d;
    //b.f_priv();
    bb.f_publ();
}
