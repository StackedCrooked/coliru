#include <iostream>
#include <limits>

using namespace std;

int main()
{
    int x = 0;

    cin >> x;
    std::cout << x << std::endl;
    std::cout << cin.good() << std::endl;
        cin >> x;
    std::cout << x << std::endl;
    std::cout << cin.good() << std::endl;
    cin.clear();
        cin >> x;
    std::cout << x << std::endl;
    std::cout << cin.good() << std::endl;

    return 0;
}