#include <iostream>

using namespace std;

struct HeavyResource
{
    int data;
};

class Wrapper
{
    HeavyResource& heavyResource;
    public:
    explicit Wrapper(HeavyResource& heavyResource): heavyResource(heavyResource) {}
};

Wrapper returnAWrapper()
{
    HeavyResource heavyResource{1};
    return Wrapper(heavyResource);
}

void useWrapperTemporarily(HeavyResource& heavyResource)
{
    Wrapper wrapper(heavyResource);
    // Do stuff with wrapper...
}

void doStuffWithResource(HeavyResource& heavyResource)
{
    // Do stuff with heavyResource WITHOUT constructing
    // a Wrapper around it...
}

int main()
{
    // Case 1: wrapper1.heavyResource is dangling, right?
    // If so, Wrapper objects needs ownership of their
    // HeavyResources.
    Wrapper wrapper1 = returnAWrapper();
    
    HeavyResource heavyResource{2};
    useWrapperTemporarily(heavyResource);
    doStuffWithResource(heavyResource); // Case 2: If Wrapper
    // objects were to have EXCLUSIVE ownership of their
    // HeavyResources, then I couldn't use a HeavyResource
    // individually after a Wrapper has been constructed around
    // it and subsequently discarded, since the HeavyResource
    // would be deleted in the Wrapper's destructor.
}