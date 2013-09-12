#include <iostream>
#include <ctime>
/* A palindromic number reads the same both ways. The largest palindrome made from the product of two 2-digit numbers is 9009 = 91 × 99.
 Find the largest palindrome made from the product of two 3-digit numbers.
*/

inline bool is_palendrome(int n) {
    if ((n/100000)!=n%10) return false;
    if ((n/10000)%10!=(n/10)%10) return false;
    if ((n/1000)%10!=(n/100)%10) return false;
    return true;
}
 
int main()
{
    int result = 0;
    clock_t begin = clock();
    for(int y=999; y>=100 && result==0; --y) {
        for(int x=999; x>=y && result==0; --x) {
            int m = x*y;
            if (is_palendrome(m))
                result = m;
        }
    }
    clock_t end = clock();
    double t = double(end-begin)/CLOCKS_PER_SEC*1000;
    std::cout << "found " << result << " in " << t << " milliseconds.";
    return 0;
}