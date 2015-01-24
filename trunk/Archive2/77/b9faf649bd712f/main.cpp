#include <iostream>

template <int S> class Environment_Where_sizeof_int_is;
template <> class Environment_Where_sizeof_int_is<8> { static const size_t foo = 12345; };
template <> class Environment_Where_sizeof_int_is<4> { static const size_t foo = 123; };
const size_t foo = Environment_Where_sizeof_int_is<3>::foo;