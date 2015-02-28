#include <iostream>

class test
{
    int member ;
public:
    test(int m) : member{m} {}
    
    const static test ob ;
    
    friend std::ostream& operator<<(std::ostream& o, const test& t)
    {
        o << t.member ;
        return o;
    }
};

const test test::ob{2};

int main()
{
    std::cout << test::ob ;
}