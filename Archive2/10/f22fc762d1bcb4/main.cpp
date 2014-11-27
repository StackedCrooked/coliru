#include <memory>

class Base {
public:
    constexpr Base(std::nullptr_t) : type(nullptr) { }
    ~Base() noexcept { delete type; }
protected:
    int* type;
};

int main()
{
    constexpr const Base d(nullptr);
    constexpr const std::unique_ptr<int> p;
}
