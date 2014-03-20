#include <string>
#include <vector>
#include <iterator>
#include <iostream>

template <typename T, size_t N> T const* begin(T const (&arr)[N]) { return arr;     }
template <typename T, size_t N> T const* end  (T const (&arr)[N]) { return arr + N; }

template <typename I, typename O>
   I copy_until(I f, I l, O o, typename std::iterator_traits<I>::value_type const& sentinel = typename std::iterator_traits<I>::value_type())
{
    while (f != l && !(*f == sentinel))
        *o++ = *f++;

    return f;
}

int main()
{
    char const* data[] = { "12", "34", "", 0 };

    std::vector<std::string> v;
    copy_until(begin(data), end(data), back_inserter(v), 0);

    std::copy(v.begin(), v.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
    std::cout << "bye\n";
}
