#include <iostream>
#include <memory>
using namespace std;

// Interface
class IFace {
public:
    virtual ~IFace () = default;
    virtual void doStuff () = 0;
};

// Implementation
class Impl : public IFace {
public:
    virtual ~Impl () { }
    virtual void doStuff () {
        cout << "Implementation is alive!" << endl;
    }
};

int main (int argc, char ** argv) {
    auto impl = std::shared_ptr<Impl> (new Impl ());
    impl->doStuff();
    return 0;
}