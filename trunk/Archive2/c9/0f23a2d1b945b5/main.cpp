#include <string>
#include <vector>

int main()
{
    std::vector<std::string> vec = {"Hello", "World"};
    vec[0][0] = 'h';
    
    return 0;
}