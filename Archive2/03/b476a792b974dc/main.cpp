#include <algorithm>
#include <iostream>
using namespace std;

/****************************************************/

#define TYPE(X) \
const char X ## _str [] = #X; \
struct X \
{ \
    static const char *name() { return X ## _str; }  \
    enum{ name_size = sizeof(X ## _str) }; \
}; \
/**/

/****************************************************/

struct nil {};

template<typename Head, typename Tail = nil>
struct List
{
    typedef Head head;
    typedef Tail tail;
};

/****************************************************/

template<typename list>
struct sum_size
{
    enum { value = list::head::name_size - 1 + sum_size<typename list::tail>::value };
};
template<>
struct sum_size<nil>
{
    enum { value = 0 };
};

/****************************************************/

template<typename list>
struct fill_string
{
    static void call(char *out)
    {
        typedef typename list::head current;
        const char *first = current::name();
        fill_string<typename list::tail>::call
        (
            copy(first, first + current::name_size - 1, out)
        );
    }
};

template<>
struct fill_string<nil>
{
    static void call(char *out)
    {
        *out = 0;
    }
};

/****************************************************/

template<typename list>
const char *concate_names()
{
    static char result[sum_size<list>::value + 1];
    static bool calculated = false;
    if(!calculated)
    {
        fill_string<list>::call(result);
        calculated = true;
    }
    return result;
}

/****************************************************/

TYPE(foo)
TYPE(bar)
TYPE(baz)

typedef List<foo, List<bar, List<baz> > > foo_list;

int main()
{
    cout << concate_names<foo_list>() << endl; 
}

