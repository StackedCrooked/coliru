#include <memory>

struct Resource {};

std::unique_ptr<Resource> allocate()
{
    return new Resource();
}
