#include <iostream>
#include <string>
#include <vector>


struct value
{
    value() = delete;
    ~value() = default;

    value(value const&) = delete;
    value& operator =(value const&) = delete;

    explicit value(int i) : i_(i)
    {
    }
private:
    int i_;
};

int main()
{
    std::vector<value> v;
    v.reserve(10);
    for (unsigned i = 0; i < 10; ++i)
        v.emplace_back(7);

}