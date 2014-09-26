#include <iostream>

void print(const char *s)
{
    using namespace std;
    cout << s << endl;
}

struct Test
{
    Test()
    {
        print("\tdefault");
    }
    Test(const Test &)
    {
        print("\tcopy");
    }
    Test &operator=(const Test &);
    void swap(Test&)
    {
        print("\tswap");
    }
};


Test method()
{
    return Test();
}

int main()
{
    print("\nnormal:");
    Test x = method();
    
    print("\nconst ref binding:");
    const Test &y = method();

    print("\nswap trick:");
    Test z;
    method().swap(z);
}
