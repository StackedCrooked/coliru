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


Test foo()
{
    return Test();
}

int main()
{
    print("\nnormal:");
    Test x = foo();
    
    print("\nconst ref binding:");
    const Test &y = foo();

    print("\nswap trick:");
    Test z;
    foo().swap(z);
}
