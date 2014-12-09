#include <iostream>
#include <string>

struct Tmp
{
    Tmp(const std::string& s) : s(s) {}
    Tmp(Tmp&& rhs) : s(rhs.s) { std::cout << "Tmp1 - Move Constructor " << rhs.s << std::endl; }
    Tmp(const Tmp& rhs) : s(rhs.s) { std::cout << "Tmp1 - Copy Constructor " << rhs.s << std::endl; }
    
    Tmp& operator=(Tmp&& rhs) { s = rhs.s; std::cout << "Tmp1 - Move Assignment" << rhs.s << std::endl; return *this; }
    Tmp& operator=(const Tmp& rhs) { s = rhs.s; std::cout << "Tmp1 - Copy Assignment" << rhs.s << std::endl; return *this; }
    
    std::string s;
};

Tmp operator+(Tmp lhs, const Tmp& rhs)
{
    lhs.s += rhs.s;
    return lhs;
}

struct Tmp2
{
    Tmp2(const std::string& s) : s(s) {}
    Tmp2(Tmp2&& rhs) : s(rhs.s) { std::cout << "Tmp2 - Move Constructor " << rhs.s << std::endl; }
    Tmp2(const Tmp2& rhs) : s(rhs.s) { std::cout << "Tmp2 - Copy Constructor " << rhs.s << std::endl; }
    
    Tmp2& operator=(Tmp2&& rhs) { s = rhs.s; std::cout << "Tmp2 - Move Assignment" << rhs.s << std::endl; return *this; }
    Tmp2& operator=(const Tmp2& rhs) { s = rhs.s; std::cout << "Tmp2 - Copy Assignment" << rhs.s << std::endl; return *this; }
    
    std::string s;
};

Tmp2 operator+(const Tmp2& lhs, const Tmp2& rhs)
{
    std::cout << "Tmp2 operator+(const Tmp2& lhs, const Tmp2& rhs)" << std::endl;
    Tmp2 tmp = lhs;
    tmp.s += rhs.s;
    return tmp;
}

Tmp2 operator+(Tmp2&& lhs, const Tmp2& rhs)
{
    std::cout << "Tmp2 operator+(Tmp2&& lhs, const Tmp2& rhs)" << std::endl;
    lhs.s += rhs.s;
    return std::move(lhs);
}

Tmp2 operator+(const Tmp2& lhs, Tmp2&& rhs)
{
    std::cout << "Tmp2 operator+(const Tmp2& lhs, Tmp2&& rhs)" << std::endl;
    rhs.s = rhs.s + lhs.s;
    return std::move(rhs);
}

Tmp2 operator+(Tmp2&& lhs, Tmp2&& rhs)
{
    std::cout << "Tmp2 operator+(Tmp2&& lhs, Tmp2&& rhs)" << std::endl;
    lhs.s += rhs.s;
    return std::move(lhs);
}

template <typename T>
void test()
{
   T s1("s1");
   T s2("s2");
   
   std::cout << "= lvalue + lvalue ==================================================================" << std::endl;
   auto r1 = s1 + s2;
   (void)r1;
   
   std::cout << std::endl;
   std::cout << "= rvalue + lvalue ==================================================================" << std::endl;
   auto r2 = T("t1") + s2;
   (void)r2;
   
   std::cout << std::endl;
   std::cout << "= lvalue + rvalue ==================================================================" << std::endl;
   auto r3 = s1 + T("t2");
   (void)r3;
   
   std::cout << std::endl;
   std::cout << "= rvalue + rvalue ==================================================================" << std::endl;
   auto r4 = T("t1") + T("t2");
   (void)r4;
}

int main()
{
   std::cout << "- Tmp --------------------------------------------------------------------" << std::endl;
   test<Tmp>();
   std::cout << std::endl;
   
   std::cout << "- Tmp2 --------------------------------------------------------------------" << std::endl;
   test<Tmp2>();
   std::cout << std::endl;
}





















