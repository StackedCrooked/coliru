#include <set>
#include <string>
#include <iostream>

int main()
{   
    std::string x;
    int n = 0;
    std::set<char> vowels;

    std::cout << "Enter any string\n";
    std::cin >> x;
    n = x.size();

    for (int i = 0; i < n; ++i)
        if (x[i] == 'a' || x[i] == 'e' || x[i] == 'i' || x[i] == 'o' || x[i] == 'u')
           vowels.insert(x[i]);

    std::cout << vowels.size() <<'\n';
}