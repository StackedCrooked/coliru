#include <iostream>
#include <random>
#include <iterator>
#include <vector>
#include <list>
#include <type_traits>
#include <utility>

namespace vsd{ namespace algorithm{

using namespace std;


std::random_device rd;
std::mt19937 gen(rd());


template<typename T>
void swap(T rhs, T lhs)
{
   if(rhs == lhs)
   {
      return;
   }

   auto tmp = rhs[0];
   rhs[0] = lhs[0];
   lhs[0] = tmp;
}


// end is exclusive
template<typename T, typename Iter>
Iter partition(Iter begin, Iter end)
{
   std::uniform_int_distribution<T> dist(0, (begin == end)? 0 : end - begin - 1);
   auto pivot_index = begin + dist(gen);
   auto index = begin - 1;

   for(auto moving_index = begin; moving_index < end; ++moving_index)
   {
      if(moving_index == pivot_index)
      {
         continue;
      }

      if(moving_index[0] < pivot_index[0])
      {

         if(++index != moving_index)
         {

            if(index == pivot_index)
            {
               pivot_index = moving_index;
            }

            vsd::algorithm::swap(index, moving_index);
         }
      }
   }

   vsd::algorithm::swap(index+1, pivot_index);

   return index + 1;
}


template<typename T>
struct TestIter
{
   static constexpr bool value = 0;
};

template<>
struct TestIter<std::random_access_iterator_tag>
{
   static constexpr bool value = 1;
};


template<typename Iter>
void qs(Iter begin, Iter end)
{
   using IterCatType = typename std::iterator_traits<Iter>::iterator_category;
   using IterDiffType = typename std::iterator_traits<Iter>::difference_type;

   static_assert(TestIter<IterCatType>::value, "Only support random_access_iterator.");

   if(end > begin)
   {
      auto pivot = partition<IterDiffType>(begin, end);

      qs(begin, pivot);

      qs(pivot + 1, end);
   }
}

}} // vsd::algorithm


template<typename T>
void CreateLargeVec(T&& vec)
{
   vec.reserve(999999);

   std::uniform_int_distribution<int> dist(-999999, 999999);
   for(auto a = 0; a < 999999 ; ++a)
   {
      vec.push_back(dist(vsd::algorithm::gen));
   }
}


int main()
{
   using namespace vsd::algorithm;
   std::vector<int> vec{9,4,2,6,6,3,1,7,5,6,16,3};
//   CreateLargeVec(vec);

   qs(vec.begin(), vec.end());

   for(auto& value : vec)
   {
      cout << value << " ";
   }
   cout << endl;
}
