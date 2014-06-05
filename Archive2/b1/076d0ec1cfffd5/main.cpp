#include <sstream>
#include <chrono>
#include <atomic>
#include <string>
#include <vector>
#include <map>


 
int main()
{
    printf("lets go\n");
    std::vector<int> vec;
    for (int i = 0; i < 10000; i++)
    {
        vec.push_back(1);
        printf("cap: %zu\n", vec.capacity());
    }
}