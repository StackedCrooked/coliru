#include <iostream>
#include <vector>

class A 
{
    public: 
        A () = default;
        A (int) {}; 
        void operator=(const A& ) { std::cout << "A const & assign" << std::endl; }
}; 

class B
{
    A a; 

    public: 

        B() = default; 
        B(int) {};  

        void operator=(const B& ) { std::cout << "B const & assign" << std::endl; }

        operator const A&() const
        {
            return a; 
        }
};


struct firstGetter
{
    template<typename Data>
    A const & getA(Data const& d) const
    {
        return d.first;
    }

    template<typename Data>
    B const & getB(Data const& d) const
    {
        return d.b; 
    }
};

struct secondGetter
: 
    public firstGetter 
{
    template<typename Data>
    A const & getA(Data const & d) const
    {
        return d.second; 
    }
};

template
<
    typename Getter 
>
class C
: 
    public Getter
{
    struct Data 
    {
        A first; 
        A second; 
        B b; 
    };

    Data d; 

    using Getter::getA; 
    using Getter::getB; 

    public: 


        C() = default; 
        C(int) {};  

        void operator=(const C& ) { std::cout << "C const & assign" << std::endl; }

        operator const A&() const
        {
            return getA(d); 
        }

        operator const B&() const
        {
            return getB(d); 
        }
};


template<typename Aggregate, typename Iterator>
void myalg(Iterator begin, Iterator end)
{
    Aggregate g; 

    for (; begin != end; ++begin)
    {
        *begin = g;  
    }
}

int main(int argc, const char *argv[])
{
    A a; 
    B b; 

    typedef C<secondGetter> Ctype; 

    Ctype c; 

    a = b; 
    a = c; 

    std::vector<A> avec = {1,2,3,4,5,6,7,8,9}; 

    std::cout << "first alg" << std::endl; 

    myalg<A>(avec.begin(), avec.end());  

    std::cout << "second alg" << std::endl; 
    myalg<B>(avec.begin(), avec.end()); 

    std::vector<B> bvec = {1,2,3,4,5,6,7,8,9}; 

    std::cout << "third alg" << std::endl; 
    myalg<C<firstGetter>>(bvec.begin(), bvec.end());  

    return 0;
}
