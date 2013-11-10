#include <memory>
#include <utility>

class Monkey
{
public:

    enum TestEnum
    {
        TEST1 = 0,
        TEST2
    };

    Monkey(int age, TestEnum e) : mE(e), mAge(age)
    {
    }


private:
    TestEnum mE;
    int mAge;
};

template <class T, typename... Arguments>
T* AllocateObject(Arguments&&... args) { return new (malloc(sizeof(T))) T(std::forward<Arguments>(args)...); }


int main(int argc, char* argv[])
{
    Monkey* m = AllocateObject<Monkey>(100, Monkey::TEST1);

    return 0;
}