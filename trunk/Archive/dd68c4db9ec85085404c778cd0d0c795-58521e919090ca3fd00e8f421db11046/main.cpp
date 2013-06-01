#include <iostream>

// short recursive function to be used as constexpr function
constexpr unsigned long divisors(unsigned long n, unsigned long c)
{
    return !c ? 0 : !(n % c) + divisors(n, c - 1);
}

int main()
{
    constexpr auto r1 = divisors(1, 1);
    constexpr auto r2 = divisors(2, 2);
    constexpr auto r3 = divisors(3, 3);
    constexpr auto r4 = divisors(4, 4);
    constexpr auto r5 = divisors(5, 5);
    constexpr auto r6 = divisors(6, 6);
    constexpr auto r7 = divisors(7, 7);
    constexpr auto r8 = divisors(8, 8);
    constexpr auto r9 = divisors(9, 9);
    static_assert( r1 == 1, "" );
    static_assert( r2 == 2, "" );
    static_assert( r3 == 2, "" );
    static_assert( r4 == 3, "" );
    static_assert( r5 == 2, "" );
    static_assert( r6 == 4, "" );
    static_assert( r7 == 2, "" );
    static_assert( r8 == 4, "" );
    static_assert( r9 == 3, "" );
    constexpr unsigned long results[] = {
        r1, r2, r3, r4, r5, r6, r7, r8, r9
    };

    std::cout << std::boolalpha;
    auto const tabs = "\t\t";
    std::cout
        << "n" << tabs
        << "RT eval" << tabs
        << "CT eval" << tabs
        << "agree?" << '\n';
    for(unsigned long i = 0; i != 9; ++i) {
        auto const n = i + 1;
        auto const result = divisors(n, n);
        std::cout
            << n << tabs
            << result << tabs
            << results[i] << tabs
            << (result == results[i]) << '\n';
    }
}