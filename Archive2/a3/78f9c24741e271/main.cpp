#include <vector>

void do_stuff( std::vector<int> values )
{
    for ( auto& i : values )
    {
        /// (Do something with i)
        i += 2;
        for ( auto& j : values )
        {
            j += i;
        }
    }
}

int main( int, char** )
{
    using namespace std;
    
    vector<int> integers = { 1, 2, 3, 4, 5 };
    
    do_stuff( integers );
    
    return 0;
}
