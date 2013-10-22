#include <iostream>
#include <string>
#include <vector>


std::vector<int> Divisors(int n) {
    
    std::vector<int> hers;
    
    hers.push_back(1); //all numbers have 1 as a factor
    
    for(int i = 2; i < (n+1)/2; i++) {
        if((n%i)==0) hers.push_back(i);
    }
    
    hers.push_back(n); //all numbers have n as a factor
    
    return hers;
}

int main()
{
    std::vector<int> ans;
    ans = Divisors(9);
    std::cout << "Divisors of 9 are: ";
    for(std::vector<int>::iterator it = ans.begin(); it != ans.end(); it++) {
        std::cout << *it << ",";
    }
    if(ans.size() < 3) std::cout << ". Thus 9 is prime" << std::endl;
    else std::cout << ". Thus 9 is not prime";
    std::cout << std::endl;
    
    ans = Divisors(7);
    std::cout << "Divisors of 7 are: ";
    for(std::vector<int>::iterator it = ans.begin(); it != ans.end(); it++) {
        std::cout << *it << ",";
    }
    if(ans.size() < 3) std::cout << ". Thus 7 is prime" << std::endl;
    else std::cout << ".  Thus 7 is not prime" << std::endl;
    std::cout << std::endl;
    
    
    
    return 0;
}
