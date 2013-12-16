#include <valarray>
#include <algorithm>

int main()
{
   std::valarray<std::valarray<int>> a;
   std::valarray<std::valarray<int>> b;
   std::valarray<std::valarray<bool>> c;
   
   std::transform(begin(a), end(a), begin(b), begin(c), [&] (std::valarray<int> a_val, std::valarray<int> b_val) -> std::valarray<bool> {
       return std::valarray<bool>(a_val == b_val);
   });
   return 0;
}