#include <cstddef>

// this does NOT compiles: error: parameter pack 'Indices' must be at the end of the template parameter list
template <size_t... Indices, typename... Types>
struct tuple_impl // : tuple_element<Indices, Types>...
{
};
int main() {
}