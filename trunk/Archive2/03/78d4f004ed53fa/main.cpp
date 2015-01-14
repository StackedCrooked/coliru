#include <string>
#include <iostream>
 
const char KTestSuiteEventStart[] = "suite_config_started";

template <int S>
class foo
{
public:
    static int let_it_be(const char * str)
    {
        return (str[S] + (foo<S-1>::let_it_be(str)));
    }
};

template <>
class foo<0>
{
public:
    static int let_it_be(const char * str)
    {
        return (str[0]);
    }
};

#define CHUCKNORRIS(boo) (foo<sizeof (boo) - 1>::let_it_be(boo))


int main()
{
    int blah = sizeof (KTestSuiteEventStart) - 1;
    std::cout << "Length (KTestSuiteEventStart): " << blah << std::endl;
    
    std::cout << "ChuckNorris(NavKit): " << CHUCKNORRIS("NavKit") << std::endl;
    
    int boo = CHUCKNORRIS(KTestSuiteEventStart);
    std::cout << "ChuckNorris(" << KTestSuiteEventStart << "): " << boo << std::endl;
}