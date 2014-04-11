#include <iostream>
#include <random>
#include <iterator>
#include <vector>
#include <list>
#include <type_traits>
#include <utility>
#include <chrono>
#include <algorithm>
#include <ostream>

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


struct FunNode
{
   int rank;
   float income;

   bool operator <(const FunNode& fn)
   {
      return rank < fn.rank;
   }

   bool operator ==(const FunNode& fn)
   {
      return rank == fn.rank;
   }
};

std::ostream& operator<<(std::ostream& os, const FunNode& obj)
{
   return os << "My rank is: " << obj.rank << ", my income is: " << obj.income;
}

void CreateLargeVec(std::vector<FunNode>& vec)
{
   vec.reserve(9);

   std::uniform_int_distribution<int> dist(1, 999999);
   for(auto a = 0; a < 9 ; ++a)
   {
      vec.push_back({dist(vsd::algorithm::gen), (float)(3.14 * dist(vsd::algorithm::gen)) });
   }
}

int main()
{
   using namespace vsd::algorithm;
   std::vector<FunNode> vec;
   CreateLargeVec(vec);

   auto start = chrono::steady_clock::now();
   qs(vec.begin(), vec.end());
   auto end = chrono::steady_clock::now();

   auto diff = end - start;

   cout << chrono::duration <double, milli> (diff).count() << " ms" << endl;
   cout << chrono::duration <double, nano> (diff).count() << " ns" << endl;
   auto diff_sec = chrono::duration_cast<chrono::nanoseconds>(diff);
   cout << diff_sec.count() << endl;

   for (auto& in : vec)
   {
      cout << in << endl;
   }
}
