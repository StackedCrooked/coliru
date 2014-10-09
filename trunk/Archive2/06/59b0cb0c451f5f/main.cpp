#include <deque>
#include <iostream>

using namespace std;
int main()
{
    std::deque<int> numbers {2, 4, 6, 8};
 
    std::cout << "Second element: " << numbers[1] << '\n';
 
    int & e = numbers[500];
    
    e++;
 
    cout << "e " << e << endl;
    std::cout << "All numbers:";
    for (auto i : numbers) {
        std::cout << ' ' << i;
    }
    std::cout << '\n';
}