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

template < typename FI, typename T >
FI myremove(FI first,FI last, const T& val)
{
    FI f = first;
    FI nxt = first;
    while ( first != last )
    {
        if (!(*first == val) )
        {
            *nxt = *first;
            ++nxt;
        }
        ++first;
        std::cout << "_____:"; print(f,last);
        std::cout << "first:" << blank_space(f,first) << "^ \n";
        std::cout << "nxt  :" << blank_space(f,nxt) << "^ \n";
        std::cout << "–-------------------------------\n";
    }
    return nxt;
}

namespace details {
template <typename FI, typename UP>
FI partition_dispatch_FI(FI first, FI last, UP pred, std::forward_iterator_tag)
{
    return first;
}

template <typename BI, typename UP>
BI partition_dispatch_BI(BI first, BI last, UP pred, std::bidirectional_iterator_tag)
{
    while(1)
    {
        while( pred(*first) )
        {
            ++first;
            if ( first == last ) break;
        }
        do
        {
            --last;
            if ( first == last ) break;
        }while( !pred(*last) );
    }
    
}
}

tenplate

int main()
{
    using collection_t = std::vector<int>;
/*  collection_t c;
    int n=0;
    std::generate_n(std::back_inserter(c),10,[&n](){
        return n++;
    } );
    auto b = c.begin();
    auto e = c.end();
    auto p = std::find(b,e,6);
    myrotate(b,p,e);*/
    
    collection_t c = {0,1,6,2,3,4,5,6,7,8,6,9};
    myremove(c.begin(), c.end(), 6);
    
    
    return 0;
}