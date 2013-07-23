#include <memory>
#include <cassert>
#include <cstring>

int main() {
    std::shared_ptr<int> obj = std::make_shared<int>(42);
    assert(*obj == 42); // original value makes this property 
    constexpr auto N = sizeof(obj);
    char buf[N];
    std::memcpy(buf, &obj, N);
    obj.reset();
    std::make_shared<int>(17); // just to prevent flukes
    std::memcpy(&obj, buf, N);
    assert(*obj == 42); // this doesn't hold anymore (in fact, the behaviour is undefined)
}