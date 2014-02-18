#ifndef MY_ITEM_HPP
#define MY_ITEM_HPP
#include <string>

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
};

#endif // MY_ITEM_HPP