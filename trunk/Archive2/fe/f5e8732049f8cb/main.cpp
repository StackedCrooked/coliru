#include <iterator>
#include <algorithm>

#include <vector>

#include <iostream>

#include <string>

template <typename I>
void print(I begin, I end)
{
    using arg_t = typename std::iterator_traits<I>::value_type;
    std::for_each( begin, end,
    [](const arg_t& a){
        std::cout << a << ' ';
    } );
    std::cout << std::endl;
}

template <typename I>
std::string blank_space(I begin, I end )
{
    return std::string(std::distance(begin,end)*2, ' ');
}

template <typename FI>
FI myrotate(FI first, FI n_first, FI last)
{
    FI f(first),p(n_first),n(n_first);
    while ( f != n )
    {
        std::iter_swap(f++,n++);
        if ( n == last )
        {
            n = p;
        }else if ( f == p )
        {
            p = n;
        }
        std::cout << "__:"; print(first,last);
        std::cout << "f :" << blank_space(first,f) << "^ " << std::endl;
        std::cout << "n :" << blank_space(first,n) << "^ " << std::endl;
        std::cout << "p :" << blank_space(first,p) << "^ " << std::endl;
        std::cout << "---------------------------\n";
    }
    return std::next(first,std::distance(n_first,last));
}


int main()
{
    using collection_t = std::vector<int>;
    collection_t c;
    int n=0;
    std::generate_n(std::back_inserter(c),10,[&n](){
        return n++;
    } );
    auto b = c.begin();
    auto e = c.end();
    auto p = std::find(b,e,6);
    myrotate(b,p,e);
    return 0;
}