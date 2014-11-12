
#include <boost/range/adaptors.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/range/algorithm_ext.hpp>
#include <boost/range/adaptor/transformed.hpp>
#include <boost/range/numeric.hpp>
#include <vector>
#include <algorithm>
#include <functional>
#include <iostream>
#include <boost/optional.hpp>

namespace srm636_div2_level_1
{ 
// using 
using namespace boost;
using namespace boost::adaptors;
using func_i_i   = std::function < int(int) >;
using func_i_b   = std::function < bool(int) >;
using func_i_i_b = std::function < bool(int, int) >;
using func_v_oi  = std::function < optional<int>(const std::vector<int>& v)>;

std::vector<int> normalize(const std::vector<int>& in)
{
  // let
  const auto min = *min_element(in);
  func_i_i   clamp_with_min = [&](int val) { return val - min; };
  func_i_b   is_even        = [] (int val) { return val % 2 == 0; };
  func_i_i   divide_2       = [] (int val) { return val / 2; };

  // in
  std::vector<int> normalized;
  push_back(normalized, in 
                        | transformed (clamp_with_min) 
                        | filtered    (is_even) 
                        | transformed (divide_2)
            );
  return normalized;
}

optional<int> int_average(const std::vector<int>& v)
{
  const auto sum = accumulate(v, 0);
  return  (sum % size(v) == 0) ? optional<int>((sum / (int)size(v))) : none;
};

int game_of_stons_count(const std::vector<int>& stones)
{
  // let
  const auto normalized = normalize(stones);
  const auto average    = int_average(normalized);
  func_i_b need_move    = [&](int val) { return val > average.get(); };
  func_i_i move_count   = [&](int val) { return val - average.get(); };

  // in
  if (normalized.size() != stones.size() || !average)
    return -1;

  return accumulate(normalized 
                    | filtered(need_move) 
                    | transformed(move_count)
                    , 0);
}

void test()
{
  std::cout << game_of_stons_count({ 7, 15, 9, 5 }) << std::endl;;
  std::cout << game_of_stons_count({ 10, 16 }) << std::endl;
  std::cout << game_of_stons_count({ 2, 8, 4 }) << std::endl;
  std::cout << game_of_stons_count({ 17 }) << std::endl;
  std::cout << game_of_stons_count({ 10, 15, 20, 12, 1, 20 }) << std::endl;

  std::cout << std::endl;
}

} // endof namespace srm636_div2_level_1



namespace srm636_div2_level_2
{
  // using 
using namespace boost;
using namespace boost::adaptors;
using func_i_i    = std::function < int(int) > ;
using func_i_b    = std::function < bool(int) > ;
using func_i_i_b  = std::function < bool(int, int) > ;
using func_v_oi   = std::function < optional<int>(const std::vector<int>& v) > ;

int sorted_count(const std::vector<int>& in)
{
  // let
  using acc_t = std::pair < std::vector<int>&, int > ;
  auto prev_read = [](acc_t& acc)->  std::vector<int>& { return acc.first; };
  auto acc_count = [](const acc_t& acc)                { return acc.second; };
  auto update    = [](acc_t& acc, int val, int count)
  { acc.first.push_back(val);  return acc_t{ acc.first, acc.second + count }; };

  std::function<acc_t(acc_t&, int)> acc_op = [&](acc_t& acc, int val)
  {
    // let
    auto  less        = [&](int prev){ return 0 < prev && prev < val; };
    auto  less_count  = (int)boost::count_if(prev_read(acc), less);
    // in
    return update(acc, val, less_count);
  };
  // in
  auto readed = std::vector<int>();
  acc_t init = acc_t{readed, 0};
  return acc_count(std::accumulate( std::begin(in), std::end(in), init, acc_op)); 
}
  

template <typename Op>
std::vector<int> transform(std::vector<int> in, Op op)
{
  std::vector<int> out;
  boost::transform(in, std::back_inserter(out), op);
  return out;
}

std::vector<int> tail(const std::vector<int>& in)
{
  std::vector<int> tailed;
  std::copy(++std::begin(in), std::end(in), std::back_inserter(tailed));
  return tailed;
}

std::vector<int> decrease_with_pivot(const std::vector<int>& in, int pivot)
{
  func_i_i decrease = [&](int val) { return (pivot < val) ? --val : val; };
  return transform(in, decrease);
}

bool exist(const std::vector<int>& in, int val)
{
  return boost::range::find(in, val) != std::end(in);
}

int sortish_div2_ways(const std::vector<int>& in, int sortedness)
{
  if (in.size() == 1)
    return (sortedness == 0) ? 1 : 0;

  if (sortedness < sorted_count(in))
    return 0;

  std::vector<int> pivots;
  if (in[0] == 0)
  {
    for (int pivot = 1; pivot <= (int)in.size(); ++pivot)
      if (!exist(in, pivot))
        pivots.push_back(pivot);
  }
  else
    pivots.push_back(in[0]);

  std::vector<int> sub_ways;
  for (auto& pivot : pivots)
  {
    auto next_in = decrease_with_pivot(tail(in), pivot);
    auto next_sortedness = sortedness - ((int)in.size() - pivot);
    auto sub_count = sortish_div2_ways(next_in, next_sortedness);
    sub_ways.push_back(sub_count);
  }

  auto ways_count = boost::accumulate(sub_ways, 0);

  return ways_count;
}

void test()
{

  std::cout << sortish_div2_ways({ 4, 0, 0, 2, 0 }, 5) << std::endl;
  std::cout << sortish_div2_ways({ 0, 0, 0, 0 }, 4) << std::endl;
  std::cout << sortish_div2_ways({ 1, 3, 2 }, 2) << std::endl;
  std::cout << sortish_div2_ways({ 1, 2, 0, 5, 0, 0 }, 2) << std::endl;
  std::cout << std::endl;
}
}

int main()
{
   srm636_div2_level_1::test();
   srm636_div2_level_2::test();
 }
