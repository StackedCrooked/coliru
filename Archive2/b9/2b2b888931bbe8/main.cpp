#include <iostream>

#include <climits>
#include <cstring>

template <typename InputIterator>
std::size_t countDiffChars( InputIterator first,
                            InputIterator last )
{
    bool lookup[1 << CHAR_BIT] {};
    std::size_t count = 0;

    while (first != last)
    {
        auto&& val = lookup[(unsigned char)*first++];
        count += !val;
        val = true;
    }

    return count;
}

int main()
{
    std::string a = "sparnus", b = "sapnus";
    for (auto const& s : {a, b})
        std::cout << countDiffChars(std::begin(s), std::end(s)) << '\n';
}
