#include <vector>
#include <memory>

int main() 
{
    std::vector<std::unique_ptr<int>> v{ std::unique_ptr<int>{ new int } };
}
