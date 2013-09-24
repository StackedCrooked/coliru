#include<vector>
#include<string>

struct Bar
{
    Bar(std::string name) : name(std::move(name)) {}
    Bar(Bar&&) noexcept = default;
    Bar& operator = (Bar&&) noexcept(noexcept(std::declval<std::string>() = std::string())) = default;
    std::string name;
};

class Foo
{
    using V = std::vector<Bar>;
protected:
    Foo(Foo&&) noexcept = default;
    Foo& operator = (Foo&&) noexcept = default;

    Foo()
    {
    }
private:
    V vectorFoo_;
};


int main()
{
    Bar bar("hello world");
}
