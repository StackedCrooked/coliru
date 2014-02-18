#include <istream>
#include <ostream>
#include "/Archive2/b1/a01cab108e93e3/main.cpp" // my_item.hpp

Item::Item() = default;

Item::Item(const std::string& name) : item_name(name) {}

Item::Item(const std::string& name, int value) : item_name(name), item_value(value) {}

std::string Item::name() const { return item_name; }
void Item::set_name(const std::string& name) { item_name = name; }

int Item::value() const { return item_value; }
void Item::set_value(int value) { item_value = value; }

std::istream& operator>>(std::istream& stream, Item& item) {
    return stream >> item.item_name >> item.item_value;
}

std::ostream& operator<<(std::ostream& stream, const Item& item) {
    return stream << item.item_name << ' ' << item.item_value;
}