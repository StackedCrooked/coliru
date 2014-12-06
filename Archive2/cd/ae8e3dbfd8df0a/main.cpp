//
// Simplest bs_array
//
// Author: Vidar Hasfjord
// Date: 2014-12-06
// Reply-to: <surname> at btinternet.com
//
// ISO/IEC JTC1/SC22/WG21 Working Paper References:
//
// Bjarne Stroustrup, "Alternatives for Array Extensions", N3810, 2013-10-13
// Jeff Snyder and Richard Smith, "Exploring classes of runtime size", N4025, 2014-05-23
// J. Daniel Garcia, "Arrays of run-time bounds as data members", N4294, 2014-11-23
//

#include <malloc.h>
#include <vector>
#include <algorithm>
#include <cassert>
#include <iostream>

//
// Simulates the proposed context-sensitive keyword `__auto_storage`.
//
// This new keyword shall only be used as the default argument for the last parameter 
// of a constructor. This parameter shall be of type `void*`.
//
// The keyword signals to the compiler that it shall:
//
// 1. Call the same class' static function `__auto_storage_size`, passing the preceding
//    arguments that were passed to the constructor.
//
// 2. Call `alloca` with the result of (1).
//
// 3. Pass the result of (2) as the last constructor argument.
//
// Arguments shall only be evaluated once throughout the construction procedure.
// More than one overloaded constructor may use `__auto_storage`, but all must
// have a matching overload for `__auto_storage_size`.
//
// A class that uses this feature is an Automatic Storage Allocating Class (ASAC).
//
const auto __auto_storage = nullptr;

//
// Simulates the construction procedure performed by the compiler for an ASAC instance.
// Note that this macro re-evaluates the arguments. The intrinsic construction
// procedure shall not do so; arguments shall be evaluated once only.
//
#define CONSTRUCT_ASAC(cls, ...)\
  cls{__VA_ARGS__, alloca(cls::__auto_storage_size(__VA_ARGS__))}

//
// Example ASAC; Array of fixed size determined at run-time
// Bike shed issue: Find a proper name for standardisation.
//
template <class T>
class bs_array
{
public:

  using value_type = T;

  static auto __auto_storage_size(size_t n) -> size_t
  {
    return n * sizeof(value_type);
  }

  bs_array(size_t n_, void* storage = __auto_storage)
    : n(n_), a(static_cast<value_type*>(storage))
  {}

  auto operator[](size_t i) -> T& { return a[i]; }
  auto operator[](size_t i) const -> const T& { return a[i]; }

  auto begin() -> T* { return a; }
  auto begin() const -> const T* { return a; }
  auto end() -> T* { return a + n; }
  auto end() const -> const T* { return a + n; }

  auto size() const -> size_t { return n; }
  auto data() -> T* { return a; }
  auto data() const -> const T* { return a; }

private:

  size_t n;
  T* a;

};

//
// Test
//
auto main() -> int
{
  using namespace std;
  using A = vector<int>;
  using B = bs_array<int>;

  auto a = A{1, 2, 3};
  auto b = CONSTRUCT_ASAC(B, a.size());

  copy(begin(a), end(a), begin(b));
  assert(equal(begin(b), end(b), begin(a)));
  cout << "Test succeeded!" << endl;
}
