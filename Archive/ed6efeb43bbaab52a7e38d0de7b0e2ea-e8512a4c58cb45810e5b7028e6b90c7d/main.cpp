#include <memory>
#include <cassert>
#include <cstring>

int main() {
    std::shared_ptr<int> obj = std::make_shared<int>(42);
    assert(*obj == 42); // this property holds under the original value

    constexpr auto N = sizeof(obj);
    char buf[N];
    std::memcpy(buf, &obj, N); // get the bits that made up the original value

    obj.reset(); // modify the original object
    std::make_shared<int>(17); // just to prevent flukes

    std::memcpy(&obj, buf, N); // try to restore the original value by restoring the bits
    assert(*obj == 42); // this doesn't hold anymore (in fact, the behaviour is undefined)
}