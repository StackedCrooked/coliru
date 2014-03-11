#include <iostream>
     
struct widget
{
    struct baz { explicit baz() { std::cout << "constructor\n"; } };
    static void baz() { std::cout << "function\n"; }
};
     
int main()
{
    typename widget::baz();
    widget::baz();
    return 0;
}