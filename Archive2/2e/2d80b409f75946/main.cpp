#include <vector>
#include <iostream>
#include <type_traits>

template<typename T> struct CorrectVector {
    typedef T        value_type;
    typedef size_t   size_type;

    struct iterator { };
    struct const_iterator { };

    const_iterator end() const { return {}; }
    
    iterator insert(const_iterator, size_type, const_reference) {
        return {};
    }
};

template <typename C> constexpr bool is_insert_pos_n_val_broken() {
    return std::is_same<void, decltype(C().insert(C().end(),1,{}))>::value;
}

int main()
{
    std::cout << "platform vector result: " << is_insert_pos_n_val_broken<std::vector<int>>()   << "\n";
    std::cout << "correct vector result: "  << is_insert_pos_n_val_broken<CorrectVector<int>>() << "\n";
}

