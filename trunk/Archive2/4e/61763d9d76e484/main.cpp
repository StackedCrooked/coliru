#include <iostream>
#include <string>
#include <vector>
#include <functional>

using std::vector;

template<typename T1>
class RREvent1Arg
{
public:
    typedef std::function<void (T1)> Func;

public:
    void Call( T1 arg )
    {
        for( auto i = m_handlers.begin(); i != m_handlers.end(); i++ )
        {
            (*i)( arg );
        }
    }

    void operator ()(T1 arg)
    {
        Call( arg );
    }

    RREvent1Arg& operator += ( Func f )
    {
        m_handlers.push_back( f );
        return *this;
    }

    RREvent1Arg& operator -= ( Func f )
    {
        for( auto i = m_handlers.begin(); i != m_handlers.end(); i++ )
        {
            if ( (*i).template target<void (T1)>() == f.template target<void (T1)>() )
            {
                m_handlers.erase( i );
                break;
            }
        }

        return *this;
    }

private:
    vector<Func> m_handlers;
};

int main() {
        
    int stackValue = 200;
    RREvent1Arg<int> e;
    e += [=](int i) { printf( "%d\n", i + stackValue ); };
    e += [&](int i) { printf( "%d\n", i + stackValue ); stackValue += 100; };
    e += [&stackValue](int i) { printf( "%d\n", i + stackValue ); };
    e += [stackValue](int i) { printf( "%d\n", i + stackValue ); };

}