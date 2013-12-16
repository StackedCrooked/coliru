#include <iostream>

void increment(int ***k)
{
    (***k)++;
}

void large_increment(int **j)
{
    for(int i = 0; i < 5; i++)
        increment(&j);
}

int main()
{
    int* i = new int(5);
    large_increment(&i);
    std::cout << *i << std::endl;
}
