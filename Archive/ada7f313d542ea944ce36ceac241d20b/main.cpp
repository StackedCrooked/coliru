

template<typename T>
const T & Decode(const T & t)
{
    return t;
}



template<typename N>
struct P
{
    template<typename Dec>
    static void foo(const Dec & dec)
    {
        P<N+1>::foo(std::make_pair(Decode(dec), dec));        
    }
};


template<>
struct P<5>
{
    template<typename Dec>
    static void foo(const Dec & )
    {
    }    
};


int main()
{
    P<1> p;
    p.foo(0);    
}