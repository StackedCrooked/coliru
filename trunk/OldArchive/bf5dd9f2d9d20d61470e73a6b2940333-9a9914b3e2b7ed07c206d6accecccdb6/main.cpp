#include <boost/container/vector.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/progress.hpp>
#include <boost/range.hpp>
#include <boost/swap.hpp>
#include <iostream>
#include <cstddef>
#include <cstdlib>
#include <string>

using namespace std;
using namespace boost;
using namespace algorithm;

bool log_alloc = false;

#ifdef LOG_ALLOCATIONS
void *operator new(size_t x)
{
    if(log_alloc) cout << "new:\t" << x << endl;
    return malloc(x);
}
void operator delete(void *p)
{
    free(p);
}

void *operator new[](size_t x)
{
    if(log_alloc) cout << "new[]:\t" << x << endl;
    return malloc(x);
}
void operator delete[](void *p)
{
    free(p);
}
#endif

typedef iterator_range<string::const_iterator> string_view;
typedef container::vector<string_view> Vector;

class Assigner
{
    static Vector *c;
public:
    typedef Vector::const_iterator const_iterator;
    typedef Vector::const_iterator iterator;

    explicit Assigner(Vector &r)
    {
        c = &r;
    }

    template<typename Iterator>
    explicit Assigner(Iterator first, Iterator last)
    {
        c->assign(first, last);
    }

    const_iterator begin() const
    {
        return c->begin();
    }
    const_iterator end() const
    {
        return c->end();
    }

    void swap(Assigner &) {}
};
Vector *Assigner::c = 0;


template<typename Container>
void test(Container &c, const string &s)
{
    size_t r = 0;
    {
        progress_timer t;
        cout << "start" << endl;
        log_alloc = true;
        for(unsigned i = 0; i < 1000000; ++i)
        {
            split(c, s, [](char c){ return c == ' '; });
            for(auto &&x : c)
                r += distance(x);
        }
        log_alloc = false;
        cout << "end" << endl;
    }
    cout << r << endl;
}

int main()
{
    string s;
    for(unsigned i = 0; i != 64; ++i)
        s += "1 ";

    Vector v;
    Assigner a(v);
    v.reserve(s.size());

    test(a, s);
    test(v, s);
}
