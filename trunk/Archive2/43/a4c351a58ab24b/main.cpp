#include <utility>
int& f() { static int i; return i; }
using ft = int&();
int&& g() { static int i; return std::move(i); }
using gt = int&&();
ft& lvalue_ref_to_function = f;
gt&& rvalue_ref_to_function = g;
