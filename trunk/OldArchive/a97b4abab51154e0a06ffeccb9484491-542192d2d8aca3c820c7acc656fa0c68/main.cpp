#include <algorithm> // for std::copy
#include <iterator>  // for std::ostream_iterator
#include <iostream>  // for std::cout
#include <string>    // for std::string
#include <cassert>   // for assert

template<typename T, size_t N, size_t M>
   void setColumn(T(&arr)[N][M], size_t col, std::string const& val)
{
    assert(col>=0 && col <M);

    for (auto& row : arr)
        row[col] = val;
}

int main()
{
    std::string arr[][7] = {
        { "0", "1", "2", "3", "4", "5" },
        { "0", "1", "2", "3", "4", "5" },
        { "0", "1", "2", "3", "4", "5" },
        { "0", "1", "2", "3", "4", "5" },
        { "0", "1", "2", "3", "4", "5" },
        { "0", "1", "2", "3", "4", "5" },
    };

    // straightforward:
    setColumn(arr, 0, "hello");

    // to make it even more concise
    auto setColumn = [&](int c, std::string const& val) mutable { ::setColumn(arr, c, val); };

    setColumn(3, "world");

    // dump it for demo purposes
    for (auto& row : arr)
    {
        std::copy(begin(row), end(row), std::ostream_iterator<std::string>(std::cout, ";"));
        std::cout << "\n";
    }

}

