#include <iostream>
#include <chrono>
/* A palindromic number reads the same both ways. The largest palindrome made from the product of two 2-digit numbers is 9009 = 91 × 99.
 Find the largest palindrome made from the product of two 3-digit numbers.
*/

//MOOING_DUCK
inline bool is_palindrome(int n) {    
    if ((n/100000)!=n%10) return false;
    if ((n/10000)%10!=(n/10)%10) return false;
    if ((n/1000)%10!=(n/100)%10) return false;
    return true;
}

inline int biggest_palindrome_mooing_duck() {
    int result = 0;
    int sum = 200;
    for(int y=999; y>=100; --y) {
        int min = sum-y;
        if (min>999) break;
        for(int x=999; x>=y && x>=min; --x) {
            int m = x*y;
            if (m>result && is_palindrome(m)) {
                result = m;
                sum = y+x;
                break;
            }
        }
    }
    return result;
}

//SEHE
inline unsigned reverse(unsigned i)
{
    unsigned r = 0;
    while (i) {
        r *= 10;
        r += i % 10;
        i /= 10;
    }
    return r;
}

inline int biggest_palindrome_sehe() {
    unsigned largest = 0;
    for (unsigned j = 999; j>99; --j) {
        for (unsigned k = j; k>99; --k) {
            const unsigned prod = j*k;
            if (prod < 100000)
                break;            
            const unsigned lhs = prod / 1000;
            const unsigned rhs = prod % 1000;
            if (lhs==reverse(rhs)) {
                if (prod>largest)
                    largest = prod;
            }
        }
    }
    return largest;
}
 
int main()
{
    auto begin = std::chrono::high_resolution_clock::now();
    int result = biggest_palindrome_mooing_duck();
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "found " << result << " in " << (end-begin).count() << " ticks.\n";
    
    begin = std::chrono::high_resolution_clock::now();
    result = biggest_palindrome_sehe();
    end = std::chrono::high_resolution_clock::now();
    std::cout << "found " << result << " in " << (end-begin).count() << " ticks.\n";
    
    return 0;
}