#include <utility>

// Provide a sensible maximum:
template <std::size_t... indices>
void callImpl( std::index_sequence<indices...> );