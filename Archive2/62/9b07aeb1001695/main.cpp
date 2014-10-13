#include <iostream>
#include <memory>

struct fizz_buzz_item
{
    virtual void print(std::ostream& out) const = 0;
};

std::ostream& operator<< (std::ostream& out, fizz_buzz_item const& item)
{
    item.print(out);
    return out;
}

namespace fizz_buzz_items {
struct fizz
  : public fizz_buzz_item
{
    void print(std::ostream& out) const override
    {
        out << "Fizz";
    }
};

struct buzz
  : public fizz_buzz_item
{
    void print(std::ostream& out) const override
    {
        out << "Buzz";
    }
};

struct fizz_buzz
  : public fizz_buzz_item
{
    void print(std::ostream& out) const override
    {
        out << "FizzBuzz";
    }
};

struct number
  : public fizz_buzz_item
{
    number(unsigned value)
      : value{value}
    {}
    
    void print(std::ostream& out) const override
    {
        out << value;
    }
    
private:
    unsigned value;
};
} // namespace fizz_buzz_items

auto fizz_buzz(unsigned value)
{
    using pointer = std::unique_ptr<fizz_buzz_item>;
    
    if (value % 15 == 0)
    {
        return pointer{new fizz_buzz_items::fizz_buzz};
    }
    else if (value % 5 == 0)
    {
        return pointer{new fizz_buzz_items::buzz};
    }
    else if (value % 3 == 0)
    {
        return pointer{new fizz_buzz_items::fizz};
    }
    else
    {
        return pointer{new fizz_buzz_items::number{value}};
    }
}

int main()
{
    for (unsigned i = 1; i <= 100; ++i)
    {
        std::cout << *fizz_buzz(i) << '\n';
    }
}