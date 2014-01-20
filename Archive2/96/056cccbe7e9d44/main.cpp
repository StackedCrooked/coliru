#include <ctime>
#include <iostream>

using namespace std;

void recurse()
{
    srand(time(NULL));
    int test = rand() % 3 + 1;
    if(test == 2)
    {
        recurse();
    }else
    {
        cout << "finished\n";
    }
}

int main()
{
    for(int i = 0; i < 10; ++i) recurse();
}