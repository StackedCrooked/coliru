// Copyright 2013 Andrew C. Morrow
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef included_6603f051_ed25_4096_8dcf_0f4a5829cacd
#define included_6603f051_ed25_4096_8dcf_0f4a5829cacd

#include <type_traits>
#include <utility>

namespace acm {
namespace detail  {

    namespace adl_swap_ns {
        using std::swap;

        template<typename T, typename U>
        class is_swappable_test {

            struct swap_not_found_type {};

            template<typename V1, typename V2>
            static auto test(V1& v1, V2& v2) -> decltype(swap(v1, v2));

            template<typename V1, typename V2>
            static auto test(...) -> swap_not_found_type;

            using test_type = decltype(test<T, U>(std::declval<T&>(), std::declval<U&>()));

        public:
            static constexpr bool value = !std::is_same<test_type, swap_not_found_type>::value;
        };

        template<bool, typename T, typename U>
        struct is_nothrow_swappable_test :
            std::conditional<noexcept(swap(std::declval<T&>(), std::declval<U&>())),
                             std::true_type, std::false_type>::type {};

        template<typename T, typename U>
        struct is_nothrow_swappable_test<false, T, U> :
            std::false_type {};

    } // namespace adl_swap_ns

    template<typename T, typename U = T>
    struct is_swappable :
        std::conditional<adl_swap_ns::is_swappable_test<T, U>::value,
                         std::true_type, std::false_type>::type {};

    template<typename T, typename U = T>
    struct is_nothrow_swappable :
        adl_swap_ns::is_nothrow_swappable_test<is_swappable<T, U>::value, T, U> {};

} // namespace detail
} // namespace acm

#endif // included_6603f051_ed25_4096_8dcf_0f4a5829cacd

struct A {
    A() {}
    ~A() {}
    A(const A&) = delete;
    A(A&&) = delete;
};

#include <iostream>
int main(int argc, char** argv) {
    if (acm::detail::is_swappable<A>::value) std::cout << "Failed test.\n";
    return 0;
}
