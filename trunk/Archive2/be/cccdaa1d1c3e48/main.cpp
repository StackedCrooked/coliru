#include <vector>
#include <memory>

int main()
{
    std::vector<std::unique_ptr<int>> vec;
    //vec.emplace_back( 0 );
    vec.emplace_back( nullptr );
}