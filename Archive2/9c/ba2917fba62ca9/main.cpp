#include <iostream>
#include <tuple>
using std::cin;
using std::cout;
using std::endl;


int main()
{
    const char *first = "sssssss";
    const char *second = "aaa";

    cout << first << endl;
    cout << second << endl;

    auto tup = std::make_tuple(second, first);
    std::tie(first, second) = tup;

    cout << first << endl;
    cout << second << endl;
    
    return 0;
}