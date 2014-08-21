#include <iostream>

template<typename T>
class Singleton
{
    friend T;
    Singleton() = default;

public:
    virtual ~Singleton() = default;

    static auto getInstance()
    -> T &
    {
        static T t;
        return t;
    }
};

class Test : public Singleton<Test>
{
    friend Singleton<Test>;
    Test(){}
};

int main()
{
    Test &t = Test::getInstance();
}
