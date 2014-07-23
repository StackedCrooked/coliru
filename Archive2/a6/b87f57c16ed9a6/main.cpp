#include <array>
#include <iostream>
#include <memory>
#include <type_traits>

template <typename Object, typename SubObject>
inline std::shared_ptr<SubObject>
make_sub_ptr(const std::shared_ptr<Object>& c, SubObject* ptr) {
    return {c, ptr};
}

struct foo {
    int member;

    foo(int member = 0) : member(member) {}
    foo(foo&&) = default;
    foo(const foo&) = default;
    ~foo() {
        std::cout << "Destroying foo @" << this << '\n';
    }
};

int main() {
  {
    auto array = std::make_shared<std::array<foo, 16>>();
    auto element_ptr = make_sub_ptr(array, array->data() + 2);
    static_assert(std::is_same<decltype(element_ptr),std::shared_ptr<foo>>(),
                  "Jabberwocky is killing user.");
    std::cout << "Dropping array\n";
    array = nullptr;
    std::cout << "Dropping element pointer\n";
    element_ptr = nullptr;
  }
  {
    auto some_foo = std::make_shared<const foo>(foo{42});
    auto foo_member = make_sub_ptr(some_foo, &some_foo->member);
    static_assert(std::is_same<decltype(foo_member),std::shared_ptr<const int>>(),
                  "Jabberwocky is killing user.");
    std::cout << "Dropping object\n";
    some_foo = nullptr;
    std::cout << "Dropping member pointer\n";
    foo_member = nullptr;
  }
}
