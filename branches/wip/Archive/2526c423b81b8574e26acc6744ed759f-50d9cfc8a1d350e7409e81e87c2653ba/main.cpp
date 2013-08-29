#include <vector>

int main()
{
    std::vector<int> vector;
    vector.push_back(0);

    std::vector<int>::const_iterator vectorItr = vector.cbegin();
    vector.erase(vectorItr);
}