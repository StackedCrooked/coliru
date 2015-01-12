#include <algorithm>
#include <iomanip>
#include <iostream>
#include <iterator>

//Direct implementation
bool is_in(int* begin, int* end, int value)
{
    for( ; begin != end; ++begin)
        if (value == *begin)
            return true;
    return false;
}

//Using standard library
bool is_in_stl(int* begin, int* end, int value)
{
    return std::find(begin, end, value) != end;
}

int main()
{
    int a[] = {1, 6};
    int b[] = {4, 8, 1, 9};
    std::cout << std::boolalpha;
    std::cout << is_in(b, b + 4, a[0]) << '\n' << //Warning, make sure that this 4 will be changed if array size changes
                 is_in_stl(std::begin(b), std::end(b), a[1]); //Generic, STL style
}