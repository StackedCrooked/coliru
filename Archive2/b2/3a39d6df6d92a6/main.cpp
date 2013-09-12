#include <iostream>
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
    bool found=false;
    for(int y=999; y>=100 && found==false; --y) {
        for(int x=999; x>=y && found==false; --x) {
            int m = x*y;
            if (is_palendrome(m)) {
                std::cout << m << '\n';
                found = true;
            }
        }
    }
    std::cout << "done\n";
    return 0;
}