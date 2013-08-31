#include <vector>

template<class T>
using func_type = void (*)(T &, T &);

func_type<std::vector> func() 
{return func_type<std::vector>();}

int main() {}