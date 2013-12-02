#include <algorithm>
#include <iostream>
#include <vector>
#include <random>
#include <limits>
using namespace std;

/*  written any integer - write a program which: finds all digits of the integer, 
writes odd and even digits from the integer, finds the biggest even and smallest 
odd numbers, writes out of odd digits the biggest possible number, writes the 
smallest possible number out of even digits. */

std::random_device rd; 
auto seed1= rd();
std::minstd_rand0 g1 (seed1);
std::uniform_int_distribution<int> dist(0, std::numeric_limits<int>::max()-1);

int get_random_int() {
    return dist(g1);
}

int main() {
    int n = get_random_int();
    std::string s = std::to_string(n);
    std::cout << "Original number: " << n << std::endl;
    for (unsigned int i = 0; i < s.size(); i++)
        std::cout << s[i] << " ";
    std::cout << std::endl;
    std::string even_numbers = "";
    std::cout << "Even numbers: ";
    std::for_each(s.begin(), s.end(), [&] (char c) {
        int n = c - '0';
        if (n % 2 == 0) {
            even_numbers += c;
            std::cout << n << " ";
        }
    });
    std::cout << " Size: " << even_numbers.size() << std::endl;
    std::string odd_numbers = "";
    std::cout << "Odd numbers: ";
    std::for_each(s.begin(), s.end(), [&] (char c) {
        int n = c - '0';
        if (n % 2 != 0) {
            odd_numbers += c;
            std::cout << n << " ";
        }
    });
    std::cout << " Size: " << odd_numbers.size() << std::endl;
    std::cout << "Max even number: " << *std::max_element(even_numbers.begin(), even_numbers.end()) << std::endl;
    std::cout << "Max odd number: " << *std::max_element(odd_numbers.begin(),  odd_numbers.end()) << std::endl;
    // reverse sort
    auto pred = [] (char a, char b) { return b < a; };
    std::sort(even_numbers.begin(), even_numbers.end());
    std::sort(odd_numbers.begin(), odd_numbers.end(), pred);
    std::cout << "Smallest number made of even number digits: " << even_numbers << std::endl;
    std::cout << "Biggest number made of odd number digits: " << odd_numbers << std::endl;
}