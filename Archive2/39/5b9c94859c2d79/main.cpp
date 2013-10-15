#include <random>
#include <iostream>
#include <string>
#include <vector>

#include <cstdlib>
#include <algorithm>
#include <iterator>

using namespace std;

int main()
{
    typedef std::vector<int> int_vec;

    srand((unsigned)time(NULL));
    int n, m;
    cout << "n = ";
    cin  >> n;
    cout << "m = ";
    cin  >> m;

    std::vector<int_vec> mas(n, int_vec(m));

    for (auto& v : mas)
        std::for_each(begin(v), end(v), [](int& i) { i = rand()%41-20; });

    cout << "Array:\n";
    for (auto const& v : mas)
    {
        std::copy(begin(v), end(v), ostream_iterator<int>(cout, "\t"));
        cout << "\n";
    }

    auto sum_ = [m](int_vec const& v) { 
        double vchar = 0;
        for (auto j = 0; j < m; j+=2)
            if(v[j] >= 0) vchar += v[j];
        return vchar;
    };

    std::vector<double> characteristic(n, 0.0);
    std::transform(begin(mas), end(mas), begin(characteristic), sum_);

    cout << "Characteristics:\n";
    std::copy(begin(characteristic), end(characteristic), ostream_iterator<double>(cout, " "));
    cout << "\n";

    std::sort(begin(characteristic), end(characteristic));

    cout << "\nSorted characteristics:\n";
    std::copy(begin(characteristic), end(characteristic), ostream_iterator<double>(cout, " "));
    cout << "\n";

    std::sort(begin(mas), end(mas), [&sum_](int_vec const& a, int_vec const& b) { return sum_(a)<sum_(b); });

    cout << "Sorted Array:\n";
    for (auto const& v : mas)
    {
        std::copy(begin(v), end(v), ostream_iterator<int>(cout, "\t"));
        cout << "\n";
    }

}
