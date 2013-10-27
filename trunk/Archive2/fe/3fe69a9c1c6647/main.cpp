#include <iostream>


using namespace std;



typedef void (*command)();

template <command c>
void execute()
{
    command();
}

void task()
{
    cout << "a" << endl;
}

int main()
{
    execute<task>();
}