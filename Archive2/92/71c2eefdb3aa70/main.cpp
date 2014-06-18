#include <type_traits>
#include <utility>

using namespace std;

int main()
{
    static_assert(is_assignable<pair<char *, int>, pair<int, int>>::value, "Bang!");
}
