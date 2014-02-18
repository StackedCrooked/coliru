#ifndef MY_HEADER_HPP
#define MY_HEADER_HPP
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
    int itam_value{};
};

#endif // MY_HEADER_HPP