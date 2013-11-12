#include <utility>
#include <vector>

int main()
{
    std::vector<int> v1;
    std::vector<int> v2;
    v1 = std::move(v2); // Function move could not be resolved.
    return 0;
}
