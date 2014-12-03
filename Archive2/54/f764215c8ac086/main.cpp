#include <vector>
#include <iostream>
 
int main()
{
    int blah = 100;
    typedef std::vector<int*> container_t;
    container_t numbers;
    for (int i = 0; i < 10; ++i)
    {
        numbers.push_back(&blah);
    }
    const container_t& cnumbers = numbers;
    
    
    for (container_t::const_iterator it = cnumbers.begin();
        it != cnumbers.end();
        ++it)
    {
        **it = 1;
    }
    
    std::cout << blah << std::endl;
}