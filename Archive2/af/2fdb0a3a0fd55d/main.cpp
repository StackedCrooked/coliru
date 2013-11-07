#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <random>
#include <vector>
#include <utility>
#include <cmath>
#include <cassert>
#include <chrono>

using duration_t = decltype(std::chrono::high_resolution_clock::now() - std::chrono::high_resolution_clock::now());

template<class T>
struct result_t
{
    std::vector<T> numbers;
    duration_t duration;
    char const* name;
};

template<class RaIt, class F>
result_t<typename std::iterator_traits<RaIt>::value_type>
apply_algorithm(RaIt p_beg, RaIt p_end, F f, char const* name)
{
    using value_type = typename std::iterator_traits<RaIt>::value_type;
    
    std::vector<value_type> inplace(p_beg, p_end);
    
    auto start = std::chrono::high_resolution_clock::now();
    
    f(inplace);
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = end - start;
    
    return {std::move(inplace), duration, name};
}


template<class T> void lightness(std::vector<T>& vec)
{
    /**
     * Sorts the array lexicographically.
     * 
     * The trick is that we have to compare digits left-to-right
     * (considering typical Latin decimal notation) and that each of
     * two numbers to compare may have a different number of digits.
     * 
     * This is very efficient in storage space, but inefficient in
     * execution time; an approach that pre-visits each element and
     * stores a translated representation will at least double your
     * storage requirements (possibly a problem with large inputs)
     * but require only a single translation of each element.
     */
    std::sort(
        begin(vec),
        end(vec),
        [](T lhs, T rhs) -> bool {
            // Returns true if lhs < rhs
            // Returns false otherwise
            const auto BASE      = 10;
            const bool LHS_FIRST = true;
            const bool RHS_FIRST = false;
            const bool EQUAL     = false;


            // There's no point in doing anything at all
            // if both inputs are the same; strict-weak
            // ordering requires that we return `false`
            // in this case.
            if (lhs == rhs) {
                return EQUAL;
            }

            // Compensate for sign
            if (lhs < 0 && rhs < 0) {
                // When both are negative, sign on its own yields
                // no clear ordering between the two arguments.
                // 
                // Remove the sign and continue as for positive
                // numbers.
                lhs *= -1;
                rhs *= -1;
            }
            else if (lhs < 0) {
                // When the LHS is negative but the RHS is not,
                // consider the LHS "first" always as we wish to
                // prioritise the leading '-'.
                return LHS_FIRST;
            }
            else if (rhs < 0) {
                // When the RHS is negative but the LHS is not,
                // consider the RHS "first" always as we wish to
                // prioritise the leading '-'.
                return RHS_FIRST;
            }

            // Counting the number of digits in both the LHS and RHS
            // arguments is *almost* trivial.
            const auto lhs_digits = (
                lhs == 0
                ? 1
                : std::ceil(std::log(lhs+1)/std::log(BASE))
            );

            const auto rhs_digits = (
                rhs == 0
                ? 1
                : std::ceil(std::log(rhs+1)/std::log(BASE))
            );

            // Now we loop through the positions, left-to-right,
            // calculating the digit at these positions for each
            // input, and comparing them numerically. The
            // lexicographic nature of the sorting comes from the
            // fact that we are doing this per-digit comparison
            // rather than considering the input value as a whole.
            const auto max_pos = std::max(lhs_digits, rhs_digits);
            for (auto pos = 0; pos < max_pos; pos++) {
                if (lhs_digits - pos == 0) {
                    // Ran out of digits on the LHS;
                    // prioritise the shorter input
                    return LHS_FIRST;
                }
                else if (rhs_digits - pos == 0) {
                    // Ran out of digits on the RHS;
                    // prioritise the shorter input
                    return RHS_FIRST;
                }
                else {
                    const auto lhs_x = (lhs / static_cast<decltype(BASE)>(std::pow(BASE, lhs_digits - 1 - pos))) % BASE;
                    const auto rhs_x = (rhs / static_cast<decltype(BASE)>(std::pow(BASE, rhs_digits - 1 - pos))) % BASE;

                    if (lhs_x < rhs_x)
                        return LHS_FIRST;
                    else if (rhs_x < lhs_x)
                        return RHS_FIRST;
                }
            }

            // If we reached the end and everything still
            // matches up, then something probably went wrong
            // as I'd have expected to catch this in the tests
            // for equality.
            assert("Unknown case encountered");
            
            // dyp: suppress warning and throw
            throw "up";
        }
    );
}

namespace ndyp
{
    // non-optimized version
	int count_digits(int p) // returns `0` for `p == 0`
	{
	    int res = 0;
	    for(; p != 0; ++res)
	    {
	        p /= 10;
	    }
	    return res;
	}
	
	// non-optimized version
	int my_pow10(unsigned exp)
	{
	    int res = 1;
	    for(; exp != 0; --exp)
	    {
	        res *= 10;
	    }
	    return res;
	}
	
	// helper to provide integers with the same number of digits
	template<class T, class U>
	std::pair<T, T> lexicographic_pair_helper(T const p, U const maxDigits)
	{
	    auto const digits = count_digits(p);
	    // append zeros so that `l` has `maxDigits` digits
	    auto const l = static_cast<T>( p  * my_pow10(maxDigits-digits) );
	    return {l, p};
	}
	
	template<class RaIt>
	using pair_vec
	    = std::vector<std::pair<typename std::iterator_traits<RaIt>::value_type,
	                            typename std::iterator_traits<RaIt>::value_type>>;
	
	template<class RaIt>
	pair_vec<RaIt> lexicographic_sort(RaIt p_beg, RaIt p_end)
	{
	    if(p_beg == p_end) return {};
	
	    auto max = *std::max_element(p_beg, p_end);
	    auto maxDigits = count_digits(max);
	
	    pair_vec<RaIt> result;
	    result.reserve( std::distance(p_beg, p_end) );
	
	    for(auto i = p_beg; i != p_end; ++i)
	        result.push_back( lexicographic_pair_helper(*i, maxDigits) );
	
	    using value_type = typename pair_vec<RaIt>::value_type;
	
	    std::sort(begin(result), end(result),
	              [](value_type const& l, value_type const& r)
	              {
	                  if(l.first < r.first) return true;
	                  if(l.first > r.first) return false;
	                  return l.second < r.second; }
	             );
	
	    return result;
	}
}

template<class T> void dyp(std::vector<T>& vec)
{
    auto pairvec = ndyp::lexicographic_sort(begin(vec), end(vec));
    std::transform(begin(pairvec), end(pairvec), begin(vec),
                   [](typename decltype(pairvec)::value_type const& e) { return e.second; });
}


namespace nnim
{
	bool comp(int l, int r)
	{
	  int lv[10] = {}; // probably possible to get this from numeric_limits
	  int rv[10] = {};
	
	  int lc = 10; // ditto
	  int rc = 10;
	  while (l || r)
	  {
	    if (l)
	    {
	      auto t = l / 10;
	      lv[--lc] = l - (t * 10);
	      l = t;
	    }
	    if (r)
	    {
	      auto t = r / 10;
	      rv[--rc] = r - (t * 10);
	      r = t;
	    }
	  }
	  while (lc < 10 && rc < 10)
	  {
	    if (lv[lc] == rv[rc])
	    {
	      lc++;
	      rc++;
	    }
	    else
	      return lv[lc] < rv[rc];
	  }
	  return lc > rc;
	}
}

template<class T> void nim(std::vector<T>& vec)
{
    std::sort(begin(vec), end(vec), nnim::comp);
}


int main()
{
    using integer_t = int;
    constexpr integer_t dist_min = 0;
    constexpr integer_t dist_max = std::numeric_limits<integer_t>::max()/10;
    constexpr std::size_t number_of_elements = 1E6;
    
    std::vector<integer_t> input;
    {
        input.reserve(number_of_elements);
        
        std::random_device rd;
        std::mt19937 gen( rd() );
        std::uniform_int_distribution<> dist(dist_min, dist_max);
        
        for(std::size_t i = 0; i < number_of_elements; ++i)
            input.push_back( dist(gen) );
    }
    
    auto b = begin(input);
    auto e = end(input);
    
    std::vector< result_t<integer_t> > res;
    
    res.push_back( apply_algorithm(b, e, lightness<integer_t>, "lightness") );
    res.push_back( apply_algorithm(b, e, dyp<integer_t>, "dyp") );
    res.push_back( apply_algorithm(b, e, nim<integer_t>, "nim") );

    auto reference_solution = res.front();
    std::cout << "reference solution: "<<reference_solution.name<<"\n\n";
    
    for(auto const& e : res)
    {
        std::cout << "solution \""<<e.name<<"\":\n";
        std::cout << "\tduration: "<<e.duration.count()<<'\n';
        
        std::cout << "\tcomparison to reference solution: ";
        if(e.numbers.size() != reference_solution.numbers.size())
        {
            std::cout << "ouput count mismatch\n";
            break;
        }
        
        auto mismatch = std::mismatch(begin(e.numbers), end(e.numbers),
                                      begin(reference_solution.numbers)).first;
        if(end(e.numbers) == mismatch)
        {
            std::cout << "exact match\n";
        }else
        {
            std::cout << "mismatch found\n";
        }
    }
}