#include <map>

struct foo{};

int main()
{
    foo f;
    std::map<int, foo> leMap;
    leMap.insert(1, f);
}
