#include <iostream>
#include <string>
#include <vector>
#include <initializer_list>

class dog
{
    public:
    int age;
    dog(int a)
    {
        age = a;
        std::string name;
    }
    dog(const iterator_list<int>& vec)
    {
        age = *(vec.begin());
    }
};

int main()
{
	
    return 0;
}
