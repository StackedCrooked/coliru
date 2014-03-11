#include <bitset>

namespace name
{
    class test
    {
    public:
        enum flag
        {
            firstflag = 1, secondflag = 2, thirdflag = 4
        };

        void foo(std::bitset<3> flags)
        {
            return;
        }
    };
}

int main(int argc, char *argv[])
{
    name::test obj;

    obj.foo(name::test::firstflag | name::test::secondflag);

    return 0;
}
