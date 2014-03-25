#include <vector>


std::vector<int>& get_vector()
{
    static std::vector<int> vec(100 * 1000);
    return vec;
}

int& get_int()
{
    static int n = 1;
    return n;
}