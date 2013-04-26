#include <functional>
#include <utility>

int main()
{
    int i = 0;
    struct {} wat = std::make_pair(std::ref(i), 0);
}