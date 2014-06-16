#include <iostream>
#include <memory>

// Interface
class IFace {
public:
    virtual ~IFace () = default;
};

// Implementation
class Impl : public IFace {
public:
    virtual ~Impl () { }
};

int main (int argc, char ** argv) {
    auto impl = std::shared_ptr<Impl> (new Impl ());
    return 0;
}