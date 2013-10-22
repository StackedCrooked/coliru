#include <iostream>
#include <string>
#include <vector>


std::vector<int> Divisors(int n) {
    std::vector<int> hers;
    hers.push_back(1);
    hers.push_back(n);
    for(int i = 2; i < (n+1)/2; i++) {
        if((n%i)==0) hers.push_back(i);
    }
    return hers;
}

int main()
{
    std::vector<int> ans;
    ans = Divisors(9);
    std::cout << "Divisors of 9 are: ";
    for(std::vector<int>::iterator it = ans.begin(); it != ans.end(); it++) {
        std::cout << *it << ", ";
    }
    std::cout << std::endl;
    
    return 0;
}
