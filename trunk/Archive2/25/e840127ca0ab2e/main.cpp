#include <vector>
template <typename...> struct parameter;

template < typename O, typename A, typename R, typename... Args>
struct parameter <R (O::*)(A, Args...)  > {
     using first_param = A;
};

struct mem_type{

    void update(std::vector<int>) {

    }
};

using mem_fn = decltype(mem_type::update);
using f_pm = parameter<mem_fn>::first_param;

int main() {
}