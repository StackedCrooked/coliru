#include <iostream>
#include <cmath>
#include <limits>
#include <iomanip>

int main(){

  const float pow_2_149 = std::pow(2,-149); // denormal number see: http://en.wikipedia.org/wiki/Denormal_number
  const float min = std::numeric_limits<float>::min() ; // smallest normal value (FLT_MIN) 
  const float lowest = std::numeric_limits<float>::lowest() ; // lowest normal value (-FLT_MAX)
  const float denorm_min = std::numeric_limits<float>::denorm_min() ; // smallest denormal value
  
  
  const float pow_2_149_by_2 = pow_2_149 / 2 ;  
  const float min_by_2 = min / 2 ; // smaller than smallest normal value, therefore denormal
  const float lowest_by_2 = lowest / 2 ; // lower than lowest normal value, therefore denormalr
  const float denorm_min_by_2 = denorm_min / 2 ; // smaller than smallest denormal value, therefore zero
  
  std::cout << std::scientific << std::setprecision( std::numeric_limits<float>::digits10 + 1 ) << std::boolalpha
            << pow_2_149 << ' '  << min << ' ' << lowest << ' ' << denorm_min << '\n' 
            << pow_2_149_by_2 << ' ' << min_by_2 << ' ' << lowest_by_2 << ' ' << denorm_min_by_2 << '\n' 
            << ( pow_2_149_by_2 == 0 ) << ' ' <<  ( min_by_2 == 0 ) << ' ' << ( lowest_by_2 == 0 ) << ' ' << ( denorm_min_by_2 == 0 ) << '\n' ;
}