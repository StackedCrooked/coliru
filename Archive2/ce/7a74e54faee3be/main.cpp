#include <iostream>
#include <string>
#include <vector>
#include <functional>

class Test {
    private:
    std::string m_str1;
    std::string m_str2;
    
    public:
     void setString1(const std::string& str)
    {
        m_str1 = str;
        std::cout << "set m_str1 to: " << m_str1 << &std::endl;
    }
    
    void setString2(const std::string& str)
    {
        m_str2 = str;
        std::cout << "set m_str2 to: " << m_str2 << &std::endl;
    }
     
    const std::string& getString1() const { return m_str1; }
    const std::string& getString2() const { return m_str2; }
};

typedef std::function<void(const std::string& )> StringSetter;

void processString(const std::string& str, StringSetter s1, StringSetter s2)
{
    s1(str);
    s2(str + "2");
}

int main()
{
    using namespace std::placeholders;
    
    Test test;
    processString("abc", std::bind(&Test::setString1, std::ref(test), _1),
                         std::bind(&Test::setString2, std::ref(test), _1));
    std::cout << "str1: " << test.getString1() << &std::endl;
    std::cout << "str2: " << test.getString2() << &std::endl;
}
