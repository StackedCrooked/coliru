#include <iostream>
#include <utility>

using namespace std;

class Test
{
public:
    Test()
    {
        cout << "Constructed." << endl;
    }

    Test(const Test& other)
    {
        cout << "Copied." << endl;
    }

    Test(Test&& other)
    {
        cout << "Moved." << endl;
    }
};

class TestCopier
{
private:
    Test _test;

public:
    TestCopier(Test test) : _test(move(test))
    {}
};

Test makeTest()
{
    cout << "Making Test." << endl;
    return Test();
}

int main()
{
    Test test = Test();
    TestCopier tc1(test);
    cout << "---" << endl;
    TestCopier tc2(makeTest());

    return 0;
}