#include <iostream>
#include <string>

#include <cstdlib>
#include <algorithm>
#include <iterator>

template <typename T>
struct my_array // non-copyable, auto-deleting
{
    explicit my_array(size_t n = 0) : n(n), data(n? new T[n] : nullptr) { }

    explicit my_array(size_t n, T defval) : my_array(n) { 
        std::fill_n(data, n, defval);
    }

    my_array(my_array const& other) : my_array(other.n) {
        std::copy(other.data, other.data + other.n, data);
    }

    my_array(my_array&& other) noexcept : my_array(0) { 
        swap(other); 
    }

    my_array& operator=(my_array other) { return swap(other); }
    ~my_array() { delete[] data; n = 0; }

    my_array& swap(my_array& other) {
        std::swap(n, other.n);
        std::swap(data, other.data);
        return *this;
    }

    size_t n;
    T* data;
};

template <typename T> static inline T*           begin(my_array<T>& arr)               { return arr.data; }
template <typename T> static inline T*           end  (my_array<T>& arr)               { return arr.data + arr.n; }
template <typename T> static inline T const*     begin(my_array<T> const& arr)         { return arr.data; }
template <typename T> static inline T const*     end  (my_array<T> const& arr)         { return arr.data + arr.n; }
template <typename T> static inline my_array<T>& swap (my_array<T>& a, my_array<T>& b) { return a.swap(b); }

int main()
{
    typedef my_array<int> int_arr;

    srand((unsigned)time(NULL));
    int n, m;
    std::cout << "n = ";
    std::cin  >> n;
    std::cout << "m = ";
    std::cin  >> m;

    my_array<int_arr> mas(n, int_arr(m));

    using namespace std;

    for (auto& v : mas)
        std::generate(begin(v), end(v), []{ return rand()%41-20; });

    cout << "Array:\n";
    for (auto const& v : mas)
    {
        std::copy(begin(v), end(v), ostream_iterator<int>(cout, "\t"));
        cout << "\n";
    }

    auto sum_ = [m](int_arr v) { 
        double vchar = 0;
        for (auto j = 0; j < m; j+=2)
            vchar += std::min(0.0, v.data[j]);

        return vchar;
    };
    
    my_array<double> characteristic(n, 0.0);
    std::transform(begin(mas), end(mas), begin(characteristic), sum_);

    cout << "Characteristics:\n";
    std::copy(begin(characteristic), end(characteristic), ostream_iterator<double>(cout, " "));
    cout << "\n";

    std::sort(begin(characteristic), end(characteristic));

    cout << "\nSorted characteristics:\n";
    std::copy(begin(characteristic), end(characteristic), ostream_iterator<double>(cout, " "));
    cout << "\n";

    std::sort(begin(mas), end(mas), [&sum_](int_arr const& a, int_arr const& b) { return sum_(a)<sum_(b); });

    cout << "Sorted Array:\n";
    for (auto const& v : mas)
    {
        std::copy(begin(v), end(v), ostream_iterator<int>(cout, "\t"));
        cout << "\n";
    }
}
