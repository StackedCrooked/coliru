#include <vector>
#include <type_traits>
#include <typeinfo>
#include <iostream>
#include <ios>

int main() {
  using namespace std;
  
  vector<bool> vb = { true, false, true, false };
  vector<int > vi = {    1,     0,    1,     0 };
  
  auto vb2 = vb[2];             // vector<bool>::reference != bool
  auto vi2 = vi[2];             // int
  decltype(auto) rvb2 = vb[2];  // vector<bool>::reference
  decltype(auto) rvi2 = vi[2];  // int&
  auto const& crvb2 = vb[2];    // vector<bool>::reference const& != bool const&
  auto const& crvi2 = vi[2];    // int const&
  
  auto ovb2 = vb2;
  ovb2 = false;                 // OOPS ovb2 has reference semantics
  cout << boolalpha << (vb[2] == true) << "\n";
  
  auto ovi2 = vi2;
  ovi2 = 0;                     // OK, ovi2 has value semantics
  cout << boolalpha << (vi[2] == 1) << "\n";
  
  static_assert(is_convertible<decltype(vb2),   vector<bool>::value_type>::value, "");  
  static_assert(is_same       <decltype(vi2),   vector<int >::value_type>::value, "");
  static_assert(is_same       <decltype(rvb2),  vector<bool>::reference>::value, "");  
  static_assert(is_same       <decltype(rvi2),  vector<int >::reference>::value, "");
  static_assert(is_convertible<decltype(crvb2), vector<bool>::const_reference>::value, "");  
  static_assert(is_same       <decltype(crvi2), vector<int >::const_reference>::value, "");
  
  vector<bool> const cvb = { true, false, true, false };
  vector<int > const cvi = {    1,     0,    1,     0 };   
  
  auto cvb2 = cvb[2];            // vector<bool>::const_reference == bool
  auto cvi2 = cvi[2];            // int
  decltype(auto) rcvb2 = cvb[2]; // vector<bool>::const_reference == bool
  decltype(auto) rcvi2 = cvi[2]; // int const&
  auto const& crcvb2 = cvb[2];   // vector<bool>::reference const& != bool const&
  auto const& crcvi2 = cvi[2];   // int const&
  
  static_assert(is_same       <decltype(cvb2),   vector<bool>::value_type>::value, "");  
  static_assert(is_same       <decltype(cvi2),   vector<int >::value_type>::value, "");
  static_assert(is_same       <decltype(rcvb2),  vector<bool>::const_reference>::value, "");  
  static_assert(is_same       <decltype(rcvi2),  vector<int >::const_reference>::value, "");
  static_assert(is_convertible<decltype(crcvb2), vector<bool>::const_reference>::value, "");  
  static_assert(is_same       <decltype(crcvi2), vector<int >::const_reference>::value, "");
  
  auto ocvb2 = cvb2;
  ocvb2 = false;                 // OK, ocvb2 has value semantics
  cout << boolalpha << (cvb[2] == true) << "\n";
  
  auto ocvi2 = cvi2;
  ocvi2 = 0;                     // OK, ocvi2 has value semantics
  cout << boolalpha << (cvi[2] == 1) << "\n";  
}