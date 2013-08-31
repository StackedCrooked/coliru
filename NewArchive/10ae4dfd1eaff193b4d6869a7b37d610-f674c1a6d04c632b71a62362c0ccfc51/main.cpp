#include <iostream>

int main()
{
 char *arr = (char *) malloc (100 * sizeof(char));
 std::cout << *((std::size_t*)arr - 1) << std::endl;
}