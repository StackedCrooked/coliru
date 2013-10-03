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

class TestCopierGood
{
private:
    Test _test;

public:
    TestCopierGood(Test test) : _test(move(test))
    {}
};

class TestCopierBad
{
private:
    Test _test;

public:
    TestCopierBad(const Test& test) : _test(test)
    {}
};

Test makeTest()
{
    cout << "Making Test." << endl;
    return Test();
}

int main()
{
    cout << "Demonstrating bad." << endl;
    Test testBad = Test();
    TestCopierBad tcbad_lvalue(testBad);
    cout << "---" << endl;
    TestCopierBad tcbad_rvalue(makeTest());
    
    cout << "---" << endl;
    cout << "Demonstrating good." << endl;
    Test testGood = Test();
    TestCopierGood tcgood_lvalue(testGood);
    cout << "---" << endl;
    TestCopierGood tcgood_rvalue(makeTest());
    return 0;
}