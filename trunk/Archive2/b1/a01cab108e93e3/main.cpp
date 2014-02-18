#ifndef MY_ITEM_HPP
#define MY_ITEM_HPP
#include <string>
#include <iosfwd>

class Item {
public:
    Item();
    Item(const std::string& name);
    Item(const std::string& name, int value);

    std::string name() const;
    void set_name(const std::string& name);

    int value() const;
    void set_value(int value);

private:
    std::string item_name{};
    int item_value{};

    friend std::istream& operator>>(std::istream& stream, Item& item);
    friend std::ostream& operator<<(std::ostream& stream, const Item& item);
};

std::istream& operator>>(std::istream& stream, Item& item);
std::ostream& operator<<(std::ostream& stream, const Item& item);

#endif // MY_ITEM_HPP