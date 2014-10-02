#include <string>
#include <type_traits>

struct member_type;
struct set_type;

struct member_type {
    member_type &operator=(set_type &&) = delete; // not allowed to assign to member_type from set_type
};

struct set_type {
    operator member_type () { // but set_type can otherwise be converted to a member_type
      return {};
    }
};


class employee {
    member_type name_;

public:
    template<typename String,
             class = std::enable_if_t<std::is_convertible<std::decay_t<String>,
                                                          decltype(name_)>::value>>
    void set_name(String &&name) {
        name_ = std::forward<String>(name);
    }
};

int main() {
    employee e;
    e.set_name(set_type{});
}