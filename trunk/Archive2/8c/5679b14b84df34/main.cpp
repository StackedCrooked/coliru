#include <iostream>
#include <string>

#include <cstdlib>
#include <algorithm>
#include <iterator>

int main()
{
    using namespace std;

    typedef int* int_arr;

    srand((unsigned)time(NULL));
    int n, m;
    cout << "n = ";
    cin  >> n;
    cout << "m = ";
    cin  >> m;

    int_arr* mas = new (nothrow) int_arr[n];
    if (!mas)
    {
        std::cerr << "out of memory\n";
        exit(255);
    }

    std::fill_n(mas, n, nullptr);
    try
    {
        std::generate_n(mas, n, [m]{ 
                auto v = new int[m]; 
                std::generate_n(v, m, [] { return rand()%41-20; }); 
                return v; 
            });

        cout << "Array:\n";
        for(auto it = mas; it != mas+n; ++it)
        {
            std::copy_n(*it, m, ostream_iterator<int>(cout, "\t"));
            cout << "\n";
        }

        auto sum_ = [m](int_arr v) { 
            double vchar = 0;
            for (auto j = 0; j < m; j+=2)
                if(v[j] >= 0) vchar += v[j];

            return vchar;
        };

        double* characteristic = nullptr;
        try
        {
            characteristic = new double[n];
            std::transform(mas, mas+n, characteristic, sum_);

            cout << "Characteristics:\n";
            std::copy_n(characteristic, n, ostream_iterator<double>(cout, " "));
            cout << "\n";

            std::sort(characteristic, characteristic+n);

            cout << "\nSorted characteristics:\n";
            std::copy_n(characteristic, n, ostream_iterator<double>(cout, " "));
            cout << "\n";

            std::sort(mas, mas+n, [&sum_](int_arr a, int_arr b) { return sum_(a)<sum_(b); });

            cout << "Sorted Array:\n";
            for(auto it = mas; it != mas+n; ++it)
            {
                std::copy_n(*it, m, ostream_iterator<int>(cout, "\t"));
                cout << "\n";
            }

            delete[] characteristic;
        }
        catch(...)
        {
            delete[] characteristic;
            throw;
        }

        for_each(mas, mas+n, [](int_arr v) { delete[] v; });
    } catch(...)
    {
        for_each(mas, mas+n, [](int_arr v) { delete[] v; });
        throw;
    }
}
