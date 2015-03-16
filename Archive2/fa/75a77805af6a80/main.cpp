#include <iostream>
#include <string>
#include <vector>

#include <algorithm>
#include <tuple>

namespace euler005 {

struct num_t {
    unsigned value;
    bool     used;
    
    auto operator ++() -> num_t& {
        ++value;
        return *this;
    }
};

inline static auto solution(unsigned limit) -> unsigned {
    std::vector<num_t> v(limit - 1);
    std::iota(v.begin(), v.end(), num_t{2u, true});
    auto last = v.end();
    auto result = 1u;
    for (auto first = v.begin(); first != last; ++first) {
        if (result % first->value != 0) {
            result *= first->value;
            std::cout << '+' << first->value << std::endl;
            for (auto it = v.begin(); it != first; ++it) {
                if (it->used && ((result / it->value) % it->value) == 0) {
                    std::cout << '-' << it->value << std::endl;
                    result /= it->value;
                    it->used = false;
                }
            }
        } else {
            first->used = false;
        }
    }
    
    return result;
}

inline static auto solution() -> unsigned {
    return solution(20u);
}

}  // namespace euler005

int main() {
    std::cout << euler005::solution() << std::endl;
}
