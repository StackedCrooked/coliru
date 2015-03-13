#include <cstdlib>
#include <stdexcept>
#include <system_error>
#include <unistd.h>
#include <string.h> // for strerror



// Low level interface for allocating and deallocating full pages.
struct PageAllocation
{   
    // Returns the native page size (usually 4096 bytes).
    static std::size_t page_size()
    {
        return sysconf(_SC_PAGESIZE);
    }
    
    // Allocates one or more contiguous pages of memory.
    // The size of the returned block will be `num_pages * page_size()`
    static void* malloc(int num_pages)
    {   
        void* memptr{};
        if (!!posix_memalign(&memptr, page_size(), num_pages * page_size()))
        {
            throw std::system_error(std::error_code(errno, std::system_category()), strerror(errno));
        }
        return memptr;
    }
    
    // Release the memory.
    static void free(void* p)
    {
        // The free() function shall free memory that has
        // previously been allocated by posix_memalign().
        std::free(p);
    }
};
    
 
 
#include <iostream>

 
int main()
{
    std::cout << "Page size=" << PageAllocation::page_size() << std::endl;
    
    PageAllocation::free(PageAllocation::malloc(10));
}

