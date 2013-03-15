#include <string>

template<typename T, unsigned>
struct Wrap
{
    template<typename ...Args>
    Wrap(Args && ...args) : obj_(std::forward<Args>(args)...) {}

    operator T() const { return obj_; }

    T obj_;
};

int main()
{
    Wrap<std::string, 0u> first = "John";
    Wrap<std::string, 1u> last = "Smith";
    last = first;
}
