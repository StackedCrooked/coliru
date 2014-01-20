#include <set>

struct A
{
    void do_nothing() {}
    int i = 0 ;
};

struct cmp
{
    bool operator() ( A& first, A& second ) const
    {
        first.do_nothing() ;
        return first.i < second.i ;
    }
};

int main()
{
    std::set< A, cmp > s ;
    s.insert( A{} ) ;
}
