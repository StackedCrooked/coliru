#include <algorithm>
#include <array>

template<class _coll, class _Fn1> inline
void apply(_coll x, _Fn1 _Func) {
    std::transform(x.begin(), x.end(), x.begin(), _Func);
}

int main() {
    apply(std::array<int,10>{}, [](int){return 1;});
}
