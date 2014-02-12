#include <type_traits>

int main()
{
    char array[1][11];

    static_assert(std::is_same<decltype((1[&array[0]])), decltype((array[1]))>::value, "");
    static_assert(&1[&array[0]] == &array[1], "");

    array[1]; // line #10
    array[1]-&array[0][0]; // line #11
    
    1[&array[0]]-&array[0][0]; // line #13
    1[&array[0]]-&array[0][0]; // line #14
}
