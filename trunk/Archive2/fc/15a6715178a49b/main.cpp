#include <array>
#include <numeric>
using namespace std;
 
template<std::size_t sz>
constexpr std::array<int,sz> range(){
  std::array<int,sz> arr{0};
  std::iota(arr.begin(),arr.end(),0);
  return arr;
}

int main()
{
    auto r = range<10>();
}