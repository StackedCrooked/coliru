#include <iostream>

class TestCls {
public:
    TestCls(TestCls *aa)
    {
        std::cout << "Works\n";
    }
};

int main(int argc, char **argv)
{
    TestCls tt(&tt);
}
