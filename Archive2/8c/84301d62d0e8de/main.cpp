#include <iostream> 
#include <list> 

using namespace std;

template <typename T>
class my_child_list : public list<T>
{
public:
    my_child_list(int a, int b) : list<T>(a, b) { }
    int get(int index)
    {
        list<int>::iterator it = this->begin();
        advance(it, index);
        
        return *it;
    } 
}; 

int main(void) 
{
    my_child_list<int> myList(5, 2);
    
    int num = myList.get(1);
} 