#include <memory>

using namespace std;

struct HeavyResource
{
    int data;
    HeavyResource(int data): data(data) {}
};

class Wrapper
{
    std::shared_ptr<HeavyResource> heavyResource;
    public:
    explicit Wrapper(const std::shared_ptr<HeavyResource>& heavyResource): heavyResource(heavyResource) {}
};

Wrapper returnAWrapper()
{
    auto heavyResource = std::make_shared<HeavyResource>(1);
    return Wrapper(heavyResource);
}

void useWrapperTemporarily(std::shared_ptr<HeavyResource> heavyResource)
{
    Wrapper wrapper(heavyResource);
    // Do stuff with wrapper...
}

void doStuffWithResource(std::shared_ptr<HeavyResource> heavyResource)
{
    // Do stuff with heavyResource WITHOUT constructing
    // a Wrapper around it...
}

int main()
{
    // Case 1.
    Wrapper wrapper1 = returnAWrapper();
    
    auto heavyResource = std::make_shared<HeavyResource>(2);
    
    // Case 2.
    useWrapperTemporarily(heavyResource);
    doStuffWithResource(heavyResource);
}