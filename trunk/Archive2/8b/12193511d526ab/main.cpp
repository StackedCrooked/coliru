#include <algorithm>
#include <vector>
#include <utility>
#include <functional>

template<typename F>
class predicate_for_first
{
    F f;
public:
    predicate_for_first(F const& f) : f(f) {}
    
    template<typename T, typename U>
    bool operator()(std::pair<T, U> const& lhs, std::pair<T, U> const& rhs)
    {
        return f(lhs.first, rhs.first);
    }
};

template <class T, class Compare>
void foo(const std::vector<T>& v, Compare comp)
{
    std::vector<std::pair<T, int> > w;
    w.reserve( v.size() );
    int j = 0;
    for(typename std::vector<T>::const_iterator i = v.begin();
        i != v.end();
        ++i)
    {
        w.push_back( std::make_pair(*i, j++) );
    }
    
    std::sort(w.begin(), w.end(), predicate_for_first<Compare>(comp));
}

int main()
{
    std::vector<double> v;
    for(int i = 0; i < 10000; ++i)
    {
        v.push_back(i * 3.14);
    }
    foo(v, std::less<double>());
}