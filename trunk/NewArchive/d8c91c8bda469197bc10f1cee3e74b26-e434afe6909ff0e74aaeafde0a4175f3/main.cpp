#include <vector>
#include <functional>
#include <future>


int main () 
{
    std::vector<std::function<void()>> vec;
    std::packaged_task<int()> task( [] { return 100; } );
    vec.push_back( std::move(task) );
}