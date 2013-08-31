#include <map>
#include <iostream>
 
int main()
{ 
    std::map<int,char> nums {{1, 'a'}, {3, 'b'}, {5, 'c'}, {7, 'd'}, {8, 'w'} };
 
    std::cout << "nums contains " << nums.size() << " elements.\n";
}