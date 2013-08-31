#include <array>
 
int main()
{
    std::array<int,3> arr;
    arr = {1,2,3};
    static_assert(false, "it worked");
}
