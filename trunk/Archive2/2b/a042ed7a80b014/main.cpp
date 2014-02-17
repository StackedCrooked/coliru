#include <iostream>
#include <string>


class my_type {
    std::string m_value;

public:
    my_type(std::string value) : m_value(std::move(value)) {}

    operator std::string() & {
        return m_value;
    }

    operator std::string() && {
        std::cout << "Moving out " << m_value << std::endl;
        
        return std::move(m_value);
        // Explicitly  do std::move is used because ref-qualifiers don't apply
        //    to data members (m_value would still be an l-value), and (N)RVO
        //    wouldn't be crazy for the compiler to apply here.
    }
};


my_type a_func_that_returns_my_type() {
    return {"val2"};
}


int main() {
    my_type val1("val1");
    
    std::string str1 = std::move(val1);
    std::string str2 = a_func_that_returns_my_type();
    
    std::cout << "str1: " << str1 << std::endl;
    std::cout << "str2: " << str2 << std::endl;
}
