#include <queue>
#include <deque>
#include <iostream>
 
int main()
{
    std::queue<int> c1;
    c1.push(5);
    std::cout << c1.size() << '\n';
 
    std::queue<int> c2(c1);
    std::cout << c2.size() << '\n';
 
    std::deque<int> deq {3, 1, 4, 1, 5};
    std::queue<int> c3(deq);
    std::cout << c3.size() << '\n';
}