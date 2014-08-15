#include <iostream>
#include <vector>
#include <boost/type_index.hpp>
 
template<typename T>
void f(const T& param)
{
  using std::cout;
  using boost::typeindex::type_id_with_cvr;
  // show T
  cout << "T = "
       << type_id_with_cvr<T>().pretty_name()
       << '\n';
  // show param's type
  cout << "param = "
       << type_id_with_cvr<decltype(param)>().pretty_name()
       << '\n';
 
}
 
class Widget {};
 
std::vector<Widget> createVec()
{
  return std::vector<Widget>(5);
}
 
int main()
{
  const auto vw = createVec();
  if (!vw.empty()) {
    f(&vw[0]);
  }
} 