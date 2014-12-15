//-- Srm631Div2Lev1 TaroGrid
//-- http://community.topcoder.com/stat?c=problem_statement&pm=13394

#include <cmath>
#include <vector>
#include <iostream>
#include <tuple>
#include <iterator>
#include <boost/range/numeric.hpp>
#include <boost/range/algorithm.hpp>


//===========================================================
auto zipwith3 = [](auto x1, auto x2, auto x3, op)
{
   std::vector<decltype(op(x1[0], x2[0], x3[0]))> out;
   auto b1 = x1.begin();
   auto b2 = x2.begin();
   auto b3 = x3.begin();
   for (;b1!=x1.end() && b2!=x2.end()&&b3!=x3.end(); ++b1, ++b2, ++b3)
       out.emplace_back(op(b1,b2,b3));
   return out
};
auto zipwith = [](auto x1, auto x2, op)
{
   std::vector<decltype(op(x1[0], x2[0], x3[0]))> out;
   auto b1 = x1.begin();
   auto b2 = x2.begin();
   for (;b1!=x1.end() && b2!=x2.end()&&b3!=x3.end(); ++b1, ++b2)
       out.emplace_back(op(b1,b2));
   return out
};

//handler (cnts,maxs,prevs) nows = (cnts',maxs',nows)
//   where cnts' = zipWith3 (\p n c -> if p==n then c+1 else 1) prevs nows cnts
//         maxs' = zipWith max cnts' maxs
using count_t = std::vector<int>;
using max_t   = td::vector<int>;
using event_t= std::string;
using acc_t  = std::tuple<count_t, max_t, event_t>;

acc_t handler(const acc_t& acc, event_t& nows)
{
    count_t& cnts = std::get<0>(acc);
    max_t  & maxs = std::get<1>(acc);
    event_t& prvs = std::get<2>(acc); 
    auto cnt2 = zipwith3(prevs, nows, cnts, 
                [](auto& p, auto& n, auto&c){return p==n?c+1:1;});
    auto max2 = zipwith(cnts2, maxs, std::max<count_t,max_t>());
    return acc_t{cnt2, maxs2, nows};    
}
         
------------------------------------------------------
taroGrid xs = maximum $ (\(_,m,_)->m) $ foldl handler ([0,0..],[0,0..],head xs) xs

//-----------------------------------------------------------
int main()
{
  jumping_able(5, 4, { 2, 5 }); // "Able"
  jumping_able(3, 4, { 4 });   // "Not Able"
  jumping_able(3, 4, { 6 });   // "Not Able"
  jumping_able(0, 1, { 100 , 100});   // "Able"
  jumping_able(300, 400, { 500});   // "Able"
  jumping_able(11, 12, { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }); // "Able"
  jumping_able(11, 12, { 1, 2, 3, 4, 5, 6, 7, 8, 9, 100 }); // "Not Able"
}
//clang++  -std=c++1y  -ldl -lcxxrt --stdlib=libc++  main.cpp && ./a.out