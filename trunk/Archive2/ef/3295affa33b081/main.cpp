#include <cstdio>
#include <cstdlib>
#include <ctime>

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

struct fileHandle
{
    fileHandle()
    {
        // RAII
        open = myFile.open();
    }

    ~fileHandle()
    {
        // RIID
        if (open)
        {
            myFile.close();
        }
    }

    bool open;
    file myFile;
};

void doStuffWithFile()
{
    fileHandle a;
    if (!a.open)
    {
        return;
    }

    /// TON OF CODE
    return; // does not leak a file
    /// TON OF CODE
}

int main(int, char**)
{
    doStuffWithFile();

    return 0;
}
