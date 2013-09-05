#include <iostream>

void some_function()
{
}

constexpr void* get_address_of_some_function()
{
    return (void*) some_function;
}

constexpr bool is_null(void* ptr)
{
 return (ptr == nullptr);
}

constexpr std::size_t get_id(void* ptr)
{
 return (is_null(ptr) ? 0 : 1 + get_id(static_cast<char*>(ptr) - 1));
}

int main()
{
 constexpr void* ptr_ = get_address_of_some_function();
 constexpr bool is_ptr_null = is_null(ptr_);
 // Uncomment the line below, and the compiles explodes (ICE)
 // constexpr std::size_t id = get_id(ptr_);
 
 std::cout << ptr_ << '\t' << is_ptr_null << std::endl;
 
 return (0);
}
