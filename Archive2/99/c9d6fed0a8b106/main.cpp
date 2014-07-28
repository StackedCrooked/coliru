#include <type_traits>

struct metadata{
    const int parameter1;
    const long parameter2;
};

static_assert( std::is_pod<metadata>::value, "Oops");

metadata describe(){
   return { 42, 1764 };
}

int main()
{
    auto x = describe();
    (void)x;
}
