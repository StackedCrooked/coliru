#include <iostream>

template<typename Message, typename Decoration, typename PrintImpl>
void print_surrounded(Message&& msg, const Decoration& decoration, const PrintImpl& print_impl)
{
    print_impl(decoration); // should forward be used?
    print_impl(" ");
    print_impl(std::forward<Message>(msg));
    print_impl(" ");
    print_impl(decoration);
}

template<typename Message, typename PrintImpl>
void pretty_print(Message&& msg, const PrintImpl& print_impl)
{
    print_surrounded(std::forward<Message>(msg), "***", print_impl);
}

int main()
{
    pretty_print("So pretty!", [](const char* msg) {
        std::cout << msg;
    });
}