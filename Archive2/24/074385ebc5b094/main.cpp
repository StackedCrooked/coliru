#include <memory>
#include <iostream>

using namespace std;
class Initable {
public:
    //virtual void terminate() = 0;

    template<typename T, typename... Ts>
    static shared_ptr<T> make_initable(const Ts &... args) {
        return shared_ptr<T>(new T(std::forward<const Ts>(args)...), [] (Initable * aptr) {
            cout << "custom deleter" << endl;
        });
    }
};

class B : public Initable {
    B() {};
    friend class Initable;
// ...
};

int main()
{
    auto b = Initable::make_initable<B>();
}