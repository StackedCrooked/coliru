#include <vector>
#include <iostream>
 
int main()
{
    std::vector<int> numbers;
 
    numbers.push_back(42);
    numbers.push_back(314159);
 std::vector<int>::iterator a=numbers.begin();
    for (int i=0;i<2;i++){
     std::cout<<a.operator*()<<endl;
     a++;
    }
 
    return 0;
}