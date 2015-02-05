#include <iostream>

#define PRINT_FUNC std::cout << __PRETTY_FUNCTION__ << "\n"
struct loud
{
    loud() { PRINT_FUNC; }
    loud(loud const&) { PRINT_FUNC; }
    loud(loud&&) { PRINT_FUNC; }
    ~loud() { PRINT_FUNC; }
};

template<typename T, int N>
struct my_init_list
{
    T (&&arr)[N];
    
    T* begin() { return arr; }
    T* end() { return arr+N; }
};

int main()
{
    std::cout << "before\n";
    my_init_list<loud, 5> x = { {loud{},loud{},loud{},loud{},loud{}} };
    std::cout << "after\n";
}