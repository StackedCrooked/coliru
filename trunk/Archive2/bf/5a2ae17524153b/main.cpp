#include <cstdlib>
#include <stdexcept>
#include <system_error>
#include <unistd.h>
#include <string.h> // strerror



namespace detail {
    

using size_type = std::int32_t;
const auto page_size = sysconf(_SC_PAGESIZE);


char* AllocatePage(size_type num_pages)
{   
    void* ptr{};
    if (!!posix_memalign(&ptr, page_size, num_pages * page_size))
    {
        throw std::system_error(std::error_code(errno, std::system_category()), strerror(errno));
    }
    return static_cast<char*>(ptr);
}


} // namespace detail



struct PageAllocator
{
    using size_type = detail::size_type;
    
    void* allocate(size_type num_pages)
    {
        return detail::AllocatePage(num_pages);
    }

    void deallocate(void* p, size_type /*num_pages*/)
    {
        std::free(p);
    }
    
private:
};
    
    
    
int main()
{
    PageAllocator alloc;
    alloc.deallocate(alloc.allocate(1), 1);
}

