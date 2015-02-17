#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <chrono>
#include <random>
#include <boost/iterator/transform_iterator.hpp>
#include <cassert>
#include <limits>
using namespace std;
using namespace chrono;

int f(int x) { return x * 5; }

template <typename InputIt, typename OutputIt, typename UnaryCallable>
void move_append(InputIt first, InputIt last, OutputIt firstOut, OutputIt lastOut, UnaryCallable fn)
{

        while (first != last && firstOut != lastOut) {
                *firstOut++ = std::move( fn(*first++) );
        }
        
            
}

void appendTransformed1( vector<int> &vec1, const std::vector<int> &vec2)
{
  auto v2begin = boost::make_transform_iterator(vec2.begin(), f);
  auto v2end   = boost::make_transform_iterator(vec2.end(), f);
  vec1.insert(vec1.end(), v2begin, v2end);
}

void appendTransformed2(std::vector<int> &vec1, const std::vector<int> &vec2)
{
  vec1.resize(vec1.size() + vec2.size());
  for (auto &&x : vec2) 
        vec1.push_back( f(x) );
  
}

void appendTransformed3(std::vector<int> &vec1, const std::vector<int> &vec2)
{
  vec1.resize (vec1.size() + vec2.size());
  transform(vec2.begin(), vec2.end(), std::inserter( vec1, vec1.end() ), f);
}

vector<int> make_vector()
{
    constexpr size_t size = 1 << 20;
    vector<int> v(size);
    random_device trng;
    mt19937_64 prng{ trng() };
    uniform_int_distribution<int> distr(0, numeric_limits<short int>::max()); // to prevent overflow for int
    
    generate(v.begin(), v.end(), [&]() { return distr(prng); } );
    
    return v;
    
}

using cast = chrono::duration<long double>;

template<typename T, typename ... Args>
auto measure(T callable, Args&& ... args) -> long double
{
    auto start = std::chrono::high_resolution_clock::now();
           callable(args...);
    auto end = std::chrono::high_resolution_clock::now() - start;  
   
    return duration_cast<cast>(end).count();
    
    
}



int main()
{ 
    auto vec1 = std::move( make_vector() );
    auto vec2 = std::move( make_vector() );
    
    auto start = std::chrono::high_resolution_clock::now();
            std::transform(vec2.begin(), vec2.end(), back_inserter(vec1), f);
    auto end = std::chrono::high_resolution_clock::now() - start;   
    
    auto r1 = duration_cast<cast>(end).count();
        
    cout << fixed;
    
    cout << "Transform Took: " <<  r1 << endl;
    
    auto vec3 = std::move( make_vector() );
    auto vec4 = std::move( make_vector() );
    vec4.resize( vec3.size() + vec4.size() );
    
    start = std::chrono::high_resolution_clock::now();
            move_append( vec3.begin(), vec3.end(), vec4.begin() + vec3.size(), vec4.end(), f);
    end = std::chrono::high_resolution_clock::now() - start;
    
    auto r2 = duration_cast<cast>(end).count();
       
    cerr << "Took move_append: " << fixed << r2 << endl;
    
    auto vec5 = std::move( make_vector() );
    auto vec6 = std::move( make_vector() );
    auto r3 = 
              measure(appendTransformed1, vec5, vec6);
              
    cerr << "appendTransformed1(boost) took: " << fixed << r3 << "\n";
    
    auto vec7 = std::move( make_vector() );
    auto vec8 = std::move( make_vector() );
    auto r4 =
              measure(appendTransformed2, vec7, vec8);
              
    cerr << "appendTransformed2 took: " << fixed << r4 << "\n";
   
    auto vec9 = std::move( make_vector() ); 
    auto vec10 = std::move( make_vector() );
    auto r5 =
            measure(appendTransformed3, vec9, vec10);
            
    cerr << "appendTransformed3 took: " << fixed << r5 << "\n";            
    
    
}
