#include <iostream>

constexpr std::size_t get_id_direct(void * ptr)
{
 return (reinterpret_cast<std::size_t>(ptr));    
}

constexpr bool is_null(void * ptr)
{
 return (ptr == nullptr);
}

constexpr std::size_t get_id(void * ptr)
{
 return (is_null(ptr) ? 0 : 1 + get_id(static_cast<char*>(ptr) - 1));
}

int main()
{
 void * ptr_ = reinterpret_cast<void *>(12345);

 std::cout << get_id(ptr_) << "\t" 
           << get_id_direct(ptr_) << std::endl;

 std::cout << get_id(&ptr_) << "\t" 
           << get_id_direct(&ptr_) << "\t" 
           << std::size_t(&ptr_) << std::endl;
 
 return (0);
}
