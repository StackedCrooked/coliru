#include <iostream>

namespace fizz_buzz_items {
struct base_item
{
    virtual void print(std::ostream& out) const = 0;
};

struct fizz
  : public base_item
{
    void print(std::ostream& out) const override {
        out << "Fizz";
    }
};

struct buzz
  : public base_item
{
    void print(std::ostream& out) const override {
        out << "Buzz";
    }
};

struct fizz_buzz
  : public base_item
{
    void print(std::ostream& out) const override {
        out << "FizzBuzz";
    }
};

struct number
  : public base_item
{
    number(unsigned value)
      : value{value}
    {}
    
    void print(std::ostream& out) const override {
        out << value;
    }
    
private:
    unsigned value;
};
} // namespace fizz_buzz_items

struct fizz_buzz_item
{
    fizz_buzz_item(fizz_buzz_items::fizz fizz) : holder{fizz}, pointer{&holder.fizz} {}
    fizz_buzz_item(fizz_buzz_items::buzz buzz) : holder{buzz}, pointer{&holder.buzz} {}
    fizz_buzz_item(fizz_buzz_items::fizz_buzz fizz_buzz) : holder{fizz_buzz}, pointer{&holder.fizz_buzz} {}
    fizz_buzz_item(fizz_buzz_items::number number) : holder{number}, pointer{&holder.number} {}
    
    union item_holder
    {
        item_holder(fizz_buzz_items::fizz fizz) : fizz{fizz} {}
        item_holder(fizz_buzz_items::buzz buzz) : buzz{buzz} {}
        item_holder(fizz_buzz_items::fizz_buzz fizz_buzz) : fizz_buzz{fizz_buzz} {}
        item_holder(fizz_buzz_items::number number) : number{number} {}
        
        fizz_buzz_items::fizz fizz;
        fizz_buzz_items::buzz buzz;
        fizz_buzz_items::fizz_buzz fizz_buzz;
        fizz_buzz_items::number number;
    } holder;
    fizz_buzz_items::base_item* pointer;
};

std::ostream& operator<< (std::ostream& out, fizz_buzz_item const& item)
{
    item.pointer->print(out);
    return out;
}

fizz_buzz_item fizz_buzz(unsigned value)
{    
    if (value % 15 == 0) {
        return {fizz_buzz_items::fizz_buzz{}};
    } else if (value % 5 == 0) {
        return {fizz_buzz_items::buzz{}};
    } else if (value % 3 == 0) {
        return {fizz_buzz_items::fizz{}};
    } else {
        return {fizz_buzz_items::number{value}};
    }
}

int main()
{
    for (unsigned i = 1; i <= 100; ++i) {
        std::cout << fizz_buzz(i) << '\n';
    }
}