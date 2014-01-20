#include <cstddef>
#include <iostream>
#include <utility>

template <size_t N>
struct silly_constant {
  static constexpr size_t size() { return N; }  
};

template <typename... Args>
using index_sequence_for = silly_constant<sizeof...(Args)>;

namespace internal {

template <typename... Args>
class unpacker {
public:
	explicit unpacker()
	{
        typedef index_sequence_for<Args...> indices_type;
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        std::cout << "sizeof...(Args)                     = " << sizeof...(Args) << std::endl;
        std::cout << "index_sequence_for<>::size()        = " << index_sequence_for<>::size() << std::endl;
        std::cout << "index_sequence_for<Args...>::size() = " << index_sequence_for<Args...>::size() << std::endl;
        std::cout << "indices_type::size()                = " << indices_type::size() << std::endl;
	}
};

} // namespace internal

int main()
{
    internal::unpacker<>{};
}