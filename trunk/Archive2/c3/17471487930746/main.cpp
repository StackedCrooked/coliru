#include <cstdio>
#include <cstdlib>
#include <ctime>

bool getRandomBool()
{
    srand (time(NULL));
    return rand() % 2;
}

struct file
{
    bool open()
    {
        puts("opened");
        return true;
    }

    void close()
    {
        puts("closed");
    }
};

void doStuffWithFile()
{
    file a;
    if (!a.open())
    {
        return;
    }

    /// TON OF CODE
    return; // leaks a file
    /// TON OF CODE

    a.close();
}

int main(int, char**)
{
    doStuffWithFile();

    return 0;
}
