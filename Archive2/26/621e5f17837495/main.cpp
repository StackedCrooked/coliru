#include <iostream>

struct Test
{
    using MFP = void (Test::*)();
    MFP mfp = &Test::a;


    void a()
    {
        std::cout << "A" << std::endl;
    }
    void b()
    {
        std::cout << "B" << std::endl;
    }
};

int main()
{
    Test t;
    (t.*(t.mfp))();
    t.mfp = &Test::b;
    (t.*(t.mfp))();
}
