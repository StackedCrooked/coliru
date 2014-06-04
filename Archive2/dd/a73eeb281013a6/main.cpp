#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <iterator>
#include <type_traits>

template<class T>
typename std::enable_if<std::is_floating_point<T>::value, T>::type 
random_val(T const &s) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<T> dis(T(0), s); 
  
  return dis(gen);  
}

template<class T>
typename std::enable_if<std::is_integral<T>::value, T>::type 
random_val(T const &s) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<T> dis(T(0), s); 
  
  return dis(gen);  
}

template<typename T>
std::vector<T> random_partition(T const &s, std::size_t const n) {
  std::vector<T> v(n - 1);
  std::generate_n(v.begin(), n - 1, [&s]() { return random_val(s); });
  std::sort(v.begin(), v.end());
  T prv = v[0];
  for(std::size_t i(1); i < v.size(); ++i) {
    T tmp = v[i];
    v[i]  = v[i] - prv;
    prv   = tmp; 
  }
  v.push_back(s - prv);
  return v;
}

auto main() -> int {
  std::vector<double> v1 = random_partition(10.0, 4);
  std::copy(v1.begin(), v1.end(), std::ostream_iterator<double>(std::cout," ") );
  std::cout << "\nSum = " << std::accumulate(v1.begin(), v1.end(), 0.0) << std::endl;
  
  std::vector<int> v2 = random_partition(10, 4);
  std::copy(v2.begin(), v2.end(), std::ostream_iterator<int>(std::cout," ") );
  std::cout << "\nSum = " << std::accumulate(v2.begin(), v2.end(), 0) << std::endl;
  return 0;
}