#include <iostream>

void increment(int ****l)
{
    (****l)++;
}

void large_increment(int ***k)
{
    for(int i = 0; i < 5; i++)
        increment(&k);
}

void very_large_increment(int **j)
{
    for(int i = 0; i < 5; i++)
        large_increment(&j);
}

int main()
{
    int* i = new int(5);
    very_large_increment(&i);
    std::cout << *i << std::endl;
}
