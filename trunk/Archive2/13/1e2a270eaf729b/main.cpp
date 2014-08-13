#include <iostream>
#include <sstream>
#include <string>

std::string as_string(std::string str) { return "`" + str + "'"; }
std::string as_string(const char* str) { return as_string(std::string(str)); }

template<typename T>
std::string as_string(T&& t) { std::stringstream ss; ss << t; return ss.str(); }

struct CheckHelper
{
    template<typename LHS_T>
    struct LHS
    {
        LHS_T m_lhs;
        std::string lhsVal;
        std::string op;
        std::string rhsVal;
        bool m_failed;

        template<typename T>
        LHS(T&& lhs) : m_lhs(std::forward<T>(lhs)) {}

        template<typename T>
        LHS& operator==(T&& rhs)
        {
            m_failed = !(m_lhs == rhs);
            if (m_failed)
            {
                lhsVal = as_string(m_lhs);
                rhsVal = as_string(rhs);
                op = "==";
            }
            
            return *this;
        }
        
        void print(const char* exprStr)
        {
            if (!m_failed) return;
            std::cout << exprStr << " [ " <<  lhsVal << " " << op << " " << rhsVal << " ]\n";
        }
    };

    template<typename T>
    LHS<T> operator->*(T&& lhs)
    {
        return LHS<T>(lhs);
    }
};

#define CHECK(expr) \
    do { \
        CheckHelper _; \
        (_->*expr).print(#expr); \
    } while (false)

int main()
{
    int x = 1;
    std::string s = "s";
    
    CHECK(x == 2);
    CHECK(2 == x);
    CHECK(s == "z");
    CHECK("z" == s);
}
