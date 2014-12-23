#include <vector>
#include <tuple>
#include <algorithm>
#include <iostream>
#include <array>
#include <functional>

struct elem
{
    int val;
    int arr;
    int index;
    bool operator> (const elem &other) const
    {
        return std::tie (val, arr, index) > std::tie (other.val, other.arr, other.index);
    }
};

int main()
{
  std::vector<int> A = {4, 2, 3}, B = {1, 2, 3};
  std::vector<elem> elems;
  int n = static_cast<int> (A.size ());
  for (int i = 0; i < static_cast<int> (A.size ()); i++)
      {
         elems.push_back ({A[i], 0, i});
         elems.push_back ({B[i], 1, i});
      }
  sort (elems.begin (), elems.end (), std::greater<elem> ());
  std::array<std::vector<int>, 2> indices;
  for (auto &ind : indices)
    ind.reserve (n);

  int cnt = 0;
  for (auto &e : elems)
    {
      auto other_arr = !e.arr;
      cnt += lower_bound (indices[other_arr].begin (), indices[other_arr].end (), e.index) - indices[other_arr].begin ();
      auto position = lower_bound (indices[e.arr].begin (), indices[e.arr].end (), e.index);
      indices[e.arr].insert (position, e.index);
    }
  std::cout << cnt << '\n';
  return 0;
}