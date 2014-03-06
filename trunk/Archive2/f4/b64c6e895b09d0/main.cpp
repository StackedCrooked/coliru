#include <type_traits>
#include <tuple>

template<class TAG, typename... DATATYPES>
struct Message {
private:
    struct dummy_type {};
public:
    template <typename T = std::tuple<DATATYPES...>>
    Message(
        typename std::enable_if<std::tuple_size<T>() >= 1, dummy_type>::type
        = dummy_type{}
    ) {}
    Message(int n) {}
    //...
};

int main() {
    Message<int, int> m1;
    Message<int> m2{1};
    Message<int> m3;
}
