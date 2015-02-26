namespace N
{
    int init()      // Definition appears first
    {
        return 42;
    }       
}

namespace N
{
    int init()      // Definition appears first
    {
        return 42;
    }
    const int x = init();
}

int main()
{
}