#include <memory>

std::unique_ptr<Resource> allocate()
{
    return new Resource();
}
