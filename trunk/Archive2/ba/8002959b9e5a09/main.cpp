    #include <sys/time.h>
    #include <cstddef>
     
    #include <algorithm>
    #include <iostream>
    #include <limits>
    #include <string>
    #include <vector>
     
    template <typename Func>
    double benchmark(Func&& f, std::size_t iterations)
    {
    f(); // warmup
     
    timeval a, b;
    gettimeofday(&a, 0);
    for (; iterations --> 0;)
    {
    f();
    }
    gettimeofday(&b, 0);
    return (b.tv_sec * (double)1e6 + b.tv_usec) -
    (a.tv_sec * (double)1e6 + a.tv_usec);
    }
     
    template <typename FuncOne, typename FuncTwo>
    std::pair<double, double> compare(FuncOne&& one, FuncTwo&& two, std::size_t const iterations) {
    std::pair<double, double> result{std::numeric_limits<double>::max(),
    std::numeric_limits<double>::max()};
     
    for (size_t i = 0; i < 5; ++i) {
    double const first = benchmark(one, iterations);
    result.first = std::min(first, result.first);
     
    double const second = benchmark(two, iterations);
    result.second = std::min(second, result.second);
    }
     
    return result;
    }
     
    struct LinearSearch {
    LinearSearch(std::vector<std::string> const& h, std::string const& n, size_t& index):
    _haystack(h), _needle(n), _index(index) {}
     
    void operator()() const {
    for (size_t i = 0, max = _haystack.size(); i != max; ++i) {
    if (_haystack[i] == _needle) { _index = i; return; }
    }
    }
     
    std::vector<std::string> _haystack;
    std::string _needle;
    size_t& _index;
    }; // struct LinearSearch
     
    struct BinarySearch {
    BinarySearch(std::vector<std::string> const& h, std::string const& n, size_t& index):
    _haystack(h), _needle(n), _index(index)
    {
    std::sort(_haystack.begin(), _haystack.end());
    }
     
    void operator()() const {
    auto const it = std::lower_bound(_haystack.begin(), _haystack.end(), _needle);
     
    if (it != _haystack.end() and *it == _needle) { _index = it - _haystack.begin(); return; }
    }
     
    std::vector<std::string> _haystack;
    std::string _needle;
    size_t& _index;
    }; // struct BinarySearch
     
     
    int main() {
    std::string const lorem =
    "Lorem ipsum dolor sit amet "
    "consectetur adipisicing elit "
    "sed do eiusmod tempor incididunt ut labore et dolore magna aliqua "
    "Ut enim ad minim veniam "
    "quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat "
    "Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur "
    "Excepteur sint occaecat cupidatat non proident "
    "sunt in culpa qui officia deserunt mollit anim id est laborum";
     
    std::vector<std::string> vec;
    std::string acc;
    for (char c: lorem) {
    if (c != ' ') { acc.push_back(c); continue; }
     
    vec.push_back(acc); acc.clear();
    }
     
    if (not acc.empty()) { vec.push_back(acc); }
     
    std::cout << vec.size() << ": " << vec.front() << ", " << vec.back() << "\n";
     
    {
    // Search first word
    size_t lindex = -1;
    size_t bindex = -1;
     
    LinearSearch const ls{vec, "Lorem", lindex};
    BinarySearch const bs{vec, "Lorem", bindex};
     
    auto const timings = compare(ls, bs, 1000);
     
    std::cout << lindex << " in " << timings.first << "\n";
    std::cout << bindex << " in " << timings.second << "\n";
    }
     
    {
    // Search middle word
    size_t lindex = -1;
    size_t bindex = -1;
     
    LinearSearch const ls{vec, "ullamco", lindex};
    BinarySearch const bs{vec, "ullamco", bindex};
     
    auto const timings = compare(ls, bs, 1000);
     
    std::cout << lindex << " in " << timings.first << "\n";
    std::cout << bindex << " in " << timings.second << "\n";
    }
     
    {
    // Search end word
    size_t lindex = -1;
    size_t bindex = -1;
     
    LinearSearch const ls{vec, "laborum", lindex};
    BinarySearch const bs{vec, "laborum", bindex};
     
    auto const timings = compare(ls, bs, 1000);
     
    std::cout << lindex << " in " << timings.first << "\n";
    std::cout << bindex << " in " << timings.second << "\n";
    }
     
    return 0;
    }