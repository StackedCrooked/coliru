#include <cstdint>
#include <functional>
#include <algorithm>
#include <set>

class ClassA {};

ClassA& operator << ( ClassA & d, int32_t )
{
    return d;
}


class ClassMain
{
public:
    void insert( ClassA & ) const;
private:
    std::set<int> m_setContainer;
};

struct InsertOpt : std::binary_function<ClassA&, int, ClassA&>
{
        ClassA & operator( )( ClassA & c, int val ) const
        {
                c << val;
                return c;
        }
};

void ClassMain::insert( ClassA & c ) const
{
    // Case II: doesn't work
    std::for_each( m_setContainer.begin( ), m_setContainer.end( ), bind1st( InsertOpt(), c ) );
}

int main() {}