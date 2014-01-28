#include <iterator>
#include <algorithm>

int main()
{
    char arr[] = "Hello";
    std::mismatch(std::begin(arr), std::end(arr),
                  std::begin(arr), std::end(arr));
}
