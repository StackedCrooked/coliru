#include <boost/variant.hpp>
#include <iostream>
#include <string>
#include <vector>


struct Book
{
    std::string to_string() const { return "Book"; }
};


struct Duck
{
    std::string toString() const { return "Duck"; }
};


struct Wolf
{
    std::string ToString() const { return "Wolf"; }

    // Does not have tostring method, but instead implements operator<<.
    friend std::ostream& operator<<(std::ostream& os, const Wolf&)
    {
        return os << "Wolf";
    }
};


struct Paper
{
    // Does not have tostring method, but instead implements operator<<.
    friend std::ostream& operator<<(std::ostream& os, const Paper&)
    {
        return os << "Paper";
    }
};


typedef boost::variant<Book, Duck, Wolf, Paper> Item;


template<int N>
struct Score : Score<N - 1> {};


template<>
struct Score<0> {};


struct Printer : boost::static_visitor<void>
{

    template<typename ItemType>
    void operator()(ItemType&& item)
    {
        print_impl(item, Score<2>{});
    }

    template<typename ItemType>
    auto print_impl(ItemType&& item, Score<2>) const -> decltype(item.to_string(), void())
    {
        std::cout << item.to_string() << std::endl;
    }

    template<typename ItemType>
    auto print_impl(ItemType&& item, Score<2>) const -> decltype(item.toString(), void())
    {
        std::cout << item.toString() << std::endl;
    }


    template<typename ItemType>
    auto print_impl(ItemType&& item, Score<2>) const -> decltype(item.ToString(), void())
    {
        std::cout << item.ToString() << std::endl;
    }

    template<typename ItemType>
    auto print_impl(ItemType&& item, Score<1>) const -> decltype(std::cout << item << std::endl, void())
    {
        std::cout << item << std::endl;
    }
};



int main()
{
    std::vector<Item> items = { Book{}, Duck{}, Wolf{}, Paper{} };

    for (auto&& item : items)
    {
        Printer printer;
        item.apply_visitor(printer);
    }

    std::cout << "sizeof(Item)=" << sizeof(Item) << std::endl;
}
