#include <type_traits>

template<typename real_t>
class vec_t {
   static_assert(
       std::is_floating_point<real_t>::value,
       "vec_t: supports floating point types only"
   );
};

template <>
class vec_t<int> {
};

int main() {
    vec_t<int> vec;   
}