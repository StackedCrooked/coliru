#include <iostream>
#include <vector>

int main()
{
    int x = 24; //the number that we want all the divisors for
    std::vector<int> divisors; //list that will keep track of divisors
    for(int i = 1; i <= x; i++) {
        if(x % i == 0) { //if i divides x without any remainder
            divisors.push_back(i); //add i to the list of divisors
        }
    }
    
    for(size_t i = 0; i < divisors.size(); i++) { //size_t is just an unsigned int
        std::cout << divisors[i];
        if(i != divisors.size() - 1) { //if this is not the last thing in the list
            std::cout << ", "; //output a comma folled by a space
        }
    }
    std::cout << "\n";
}
