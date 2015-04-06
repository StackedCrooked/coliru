#include <algorithm>
#include <iostream>
#include <iterator>

int main(int argc, char *argv[])
{
    std::copy_n(argv, argc, std::ostream_iterator<char *>(std::cout, " "));
}