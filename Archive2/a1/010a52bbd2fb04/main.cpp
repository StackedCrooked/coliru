#include <memory>
using std::unique_ptr;

class B {
    unique_ptr<int> ref;
public:
    B(int* ptr) : ref(ptr)
        {  }
};
// The next class can not be even compiled!
class C {
    B arrayOfB[2] = { NULL, NULL };
};

int main(){
    C c;
}