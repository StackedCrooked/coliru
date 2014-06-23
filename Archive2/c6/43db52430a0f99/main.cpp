#include <functional>

namespace my_space {
    template<typename... R> 
    using bind = std::bind<R...>;
}

int main() {}