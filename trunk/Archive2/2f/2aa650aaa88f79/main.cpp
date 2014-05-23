#include <iostream>

struct S{
    template<class IdsT, class DataT>
    struct CallbackPack{
        CallbackPack(IdsT & selfIds) : selfIds_(selfIds) {}

        const IdsT & selfIds_;
    };    

    const  CallbackPack<S, S> callbackPack123 {*this};
};

int main() {
    S s;
    std::cout << "done";
    return 0;
}