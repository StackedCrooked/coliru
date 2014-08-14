#include <vector>
#include <bitset>

int main()
{
    std::vector<std::bitset<128>> myVector;
    std::bitset<128> b;
    myVector.push_back(b);
}