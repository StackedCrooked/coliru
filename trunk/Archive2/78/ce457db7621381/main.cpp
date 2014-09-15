#include <iostream>
#include <string>
#include <vector>
#include <memory>

#if 1
class Foo
{
    virtual std::unique_ptr<Foo> clone();
};

class Bar : public Foo
{
    std::unique_ptr<Bar> clone() override;
};

#else

class Foo
{
    virtual Foo* clone();
};

class Bar : public Foo
{
    Bar* clone() override;
};

#endif

int main()
{
    std::cout << "OK"<< std::endl;
}
