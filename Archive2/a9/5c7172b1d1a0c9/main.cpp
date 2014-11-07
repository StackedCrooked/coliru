#include <iostream>
#include <type_traits>

namespace non_std {
template <typename T>
inline constexpr typename std::remove_reference<T>::type &make_ref(T &&r) noexcept {
    using U = typename std::remove_reference<T>::type;
    return static_cast<U &>(r);
}
}

using namespace std;
using namespace non_std;

void divs(int &a, int &b) {
    int t = a;
    a = a / b;
    b = t / b;
}

int main() {
    int i_care_for_this_one = 4;
    divs(i_care_for_this_one, make_ref(2));
    cout << i_care_for_this_one << endl;
}