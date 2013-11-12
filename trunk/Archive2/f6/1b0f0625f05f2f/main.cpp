#include <iterator>
#include <algorithm>
#include <forward_list>
#include <iostream>
 
template <class ForwardIt>
 ForwardIt choose_pivot(ForwardIt first, ForwardIt last)
 {
   return std::next(first, std::distance(first,last)/2);
 }
 
template <class ForwardIt>
 void quicksort(ForwardIt first, ForwardIt last)
 {
    using T = typename std::iterator_traits<ForwardIt>::value_type;
 
    if(first == last) return;
    int a = 0;
    T pivot = *choose_pivot(first,last);
 
    ForwardIt middle1 = std::partition(first, last, 
                         [pivot, a](const T& em){ return em < pivot;});
    ForwardIt middle2 = std::partition(middle1, last, 
                         [pivot](const T& em){ return !(pivot < em); });
 
    quicksort(first, middle1);
    quicksort(middle2, last);
    
 }
 
 
int main()
{
   std::forward_list<int> fl = {1, 30, -4, 3, 5, -4, 1, 6, -8, 2, -5, 64, 1, 92};
 
   quicksort(std::begin(fl), std::end(fl));
 
   for(int fi : fl) std::cout << fi << ' ';
   std::cout << '\n';
}