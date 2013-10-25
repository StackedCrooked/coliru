#include <array>
#include <iostream>
 using namespace std;
int main()
{
    std::array< int, 5 > numbers {2, 4, 6, 8};
 
    std::cout << "Second element: " << numbers[1] << '\n';
 
    numbers[0] = 5;
    
    cout << numbers[10] << endl;
    numbers[10] = 1488;
    cout << numbers[10] << endl;
 
    std::cout << "All numbers:";
    for (auto i : numbers) {
        std::cout << ' ' << i;
    }
    std::cout << '\n';
}