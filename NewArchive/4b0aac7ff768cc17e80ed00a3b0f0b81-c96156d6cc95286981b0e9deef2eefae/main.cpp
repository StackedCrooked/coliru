#include <iostream>

namespace N {
    
struct Test
{
    int data[2];
};

}

int const* begin(N::Test const& t) { return &(t.data[0]); }
int const* end  (N::Test const& t) { return begin(t) + 2; }

int main()
{
        N::Test arr { 1, 2 };
        for(auto i: arr)
            std::cout << i << "\n";
}