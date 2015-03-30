#include <iostream>
#include <exception>

using namespace std;

class Test
{
public:
    Test() { throw exception{"WOO!"}; }
}

class Experiment
{
    int size{};
    int length{};
public:
    Experiment(int i = 0; int j = 0)
    try
    {
        size{i};
        length{j};
        Test t{};
    }
    catch (exception& e)
    {
        throw;
    }
};

int main(void)
{
    try
    {
        Experiment(2, 1);
    }
    catch (const exception& e)
    {
        cout << e.what() << endl;
    }
    
}

