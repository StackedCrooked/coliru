#include <iostream>

// Should PrintImpl be passed as `const PrintImpl&` or as `PrintImpl&&` ?
template<typename Message, typename PrintImpl>
void pretty_print(Message&& msg, const PrintImpl& print_impl)
{
    // stars are pretty
    print_impl("*** ");
    print_impl(std::forward<Message>(msg));
    print_impl(" ***\n");
}

int main()
{
    pretty_print("So pretty!", [](const char* msg) {
        std::cout << msg;
    });
}