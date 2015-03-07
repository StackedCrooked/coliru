#ifndef __COMBINATORIAL_INDEX_H__
#define __COMBINATORIAL_INDEX_H__

#include <vector>

namespace LTE_COMMON {
  namespace combinatorial {

    typedef long long int index_type ;
    typedef int element_type ;

/*
  Functions for working with combinatorial indices as defined in 36.213
  for the following applications

  UE-selected subband CQI reporting:    36.213 section 7.2.1
  Uplink resource allocation:           36.213 section 8.1.2
  EPDCCH RB allocation:                 36.213 section 9.1.4.4

  Note that EPDCCH RB allocation is specified by a combinatorial index that
  can be as large as 38 bits to be able to hold indices as large as C(100, 8)
  and therefore requires a 64-bit integer type.
*/

/*
  Extended binomial coefficient as defined in 36.213
  Returns a regular binomial coefficient or zero.
*/
    index_type extended_binomial_coefficient(int n, int k) ;

/*
  Given a subset of size k taken from a set of size n,
  calulate its combinatorial index as defined in 36.213.
  Input vector must be sorted in increasing order.
*/
    index_type combinatorial_index(int n, const std::vector<element_type> &v) ;

/*
  Given a subset of size k taken from a set of size n,
  calulate its combinatorial index as defined in 36.213.
  Does not require input vector to be sorted.
*/
    index_type combinatorial_index_unsorted(int n, const std::vector<element_type> &v) ;

/*
  Return an ordered subset of size k taken from a set of size n
  specified by its combinatorial index defined in 36.213.
*/
    std::vector<element_type> subset_from_index(int n, int k, index_type index) ;

/*
  Alternative version of subset_from_index.

  This version computes binomial coefficients internally without boost or lookup tables.

  It performs a linear search and takes advantage of the fact that it can
  incrementally build up a binomial coefficient C(n+1, k) based on C(n, k)
*/
    std::vector<element_type> subset_from_index_incremental(int n, int k, index_type index) ;

  } // namespace combinatorial
} // namespace LTE_COMMON

#endif // __COMBINATORIAL_INDEX_H__

#include <vector>
#include <boost/math/special_functions/binomial.hpp>
#include <boost/math/special_functions/round.hpp>
#include <boost/numeric/conversion/cast.hpp>

/*
  Functions for working with combinatorial indices as defined in 36.213
  for the following applications:

  UE-selected subband CQI reporting:    36.213 section 7.2.1
  Uplink resource allocation:           36.213 section 8.1.2
  EPDCCH RB allocation:                 36.213 section 9.1.4.4

  Note that EPDCCH RB allocation is specified by a combinatorial index that
  can be as large as 38 bits to be able to hold indices as large as C(100, 8)
  and therefore requires a 64-bit integer type.
*/

namespace LTE_COMMON {
  namespace combinatorial {
/*
  Extended binomial coefficient as defined in 36.213
  Returns a regular binomial coefficient or zero.
*/
    index_type extended_binomial_coefficient(int n, int k)
    {
      if (n < k) { return 0 ; }
      double result_double = boost::math::binomial_coefficient<double>(n, k) ;
      long long int result_long_long = boost::math::llround<double>(result_double) ;
      return boost::numeric_cast<index_type>(result_long_long) ;
    }

/*
  Given a subset of size k taken from a set of size n,
  calulate its combinatorial index as defined in 36.213.
  Input vector must be sorted in increasing order.
*/
    index_type combinatorial_index(int n, const std::vector<element_type> &v)
    {
      int k = int(v.size()) ;
      index_type sum = 0 ;
      for (int i = 0 ; i < k ; ++i)
      {
        if ((i > 1) && (v[i] <= v[i-1]))
        {
          throw std::runtime_error("vector was not sorted") ;
        }
        int x = n - int(v[i]) - 1 ;
        int y = k - i ;
        sum += extended_binomial_coefficient(x, y) ;
      }
      return sum ;
    }

/*
  Given a subset of size k taken from a set of size n,
  calulate its combinatorial index as defined in 36.213.
  Does not require input vector to be sorted.
*/
    index_type combinatorial_index_unsorted(int n, const std::vector<element_type> &v)
    {
      // Combinatorial index is defined based on the elements being indexed
      // in increasing order
      std::vector<element_type> v_sorted = v ;
      std::sort(v_sorted.begin(), v_sorted.end()) ;
      return combinatorial_index(n, v_sorted) ;
    }

/*
  Return an ordered subset of size k taken from a set of size n
  specified by its combinatorial index defined in 36.213.

  Adpated from
  http://stackoverflow.com/questions/561/using-combinations-of-sets-as-test-data#794
*/
    std::vector<element_type> subset_from_index(int n, int k, index_type index)
    {

      // Remainder of the combinatorial index after subtracting terms computed so far
      index_type remainder = index ;

      // Allocate a vector to store the return value
      std::vector<element_type> v(k) ;

      // m_first is the largest known element that cannot be used in the set
      int m_first = -1 ;

      for (int i = 0 ; i < k ; ++i)
      {
        // Compute the i-th term v[i] = m in the combinatorial index calculation

        // Perform a binary search from m_first to m_last to find the smallest element m
        // whose contribution does not exceed the remainder

        // Initialize m_last to be the smallest element whose contribution is trivially 0
        int m_last = n - k + i ;

        while (m_first < m_last - 1)
        {
          // Try the midpoint of the range (m_first, m_last)
          int m = (m_first + m_last) / 2 ;

          index_type contribution = extended_binomial_coefficient(n - m - 1, k - i);
          if (contribution > remainder)
          {
            // m_first is the largest known value that cannot be used in the set
            m_first = m ;
          }
          else
          {
            // m_last is the smallest known value that could possibly be used in the set
            m_last = m ;
          }
        }

        // Store the chosen element in the result array
        int m = m_last ;
        v[i] = element_type(m) ;

        // Account for the contribution of this element by updating the remainder
        index_type contribution = extended_binomial_coefficient(n - m - 1, k - i);
        remainder -= contribution ;

        // Require subsequent elements to have larger values
        ++m_first ;

      }

      if (remainder != 0)
      {
        throw std::runtime_error("Invalid combinatorial index") ;
      }

      return v ;

    }

/*
  Alternative version of subset_from_index.

  This version computes binomial coefficients internally without boost or lookup tables.

  It performs a linear search and takes advantage of the fact that it can
  incrementally build up a binomial coefficient C(n+1, k) based on C(n, k)
*/
    std::vector<element_type> subset_from_index_incremental(int n, int k, index_type index)
    {
      // Remainder of the combinatorial index after subtracting terms computed so far
      index_type remainder = index ;

      // Allocate a vector to store the return value
      std::vector<element_type> v(k) ;

      // m_first is the largest known element that cannot be used in the set
      int m_first = -1 ;

      int i = 0 ;
      // Perform a linear search for the smallest element m
      // whose contribution does not exceed the remainder
      while (i < k - 1)
      {
        // Compute the i-th term v[i] = m in the combinatorial index calculation
        if (remainder == 0)
        {
          break ;
        }

        int m = n + i - k - 1 ;
        index_type contribution = 1 ;
        while (m > m_first)
        {
          // Incrementally compute the next binomial coefficient C(a+1, b) based on C(a, b)
          // In this case,  a = (n-m-1), b = (k-i)
          index_type next_contrib = contribution ;
          next_contrib *= (n - m) ;
          next_contrib /= (n - m + i - k) ;

          if (next_contrib <= remainder)
          {
            // Element 'm-1' is also suitable, so keep on going
            --m ;
            contribution = next_contrib ;
          }
          else
          {
            // Element 'm' is suitable and element 'm-1' is not suitable
            // Keep the old value of 'contribution' and drop out of the loop
            break ;
          }
        }

        // Store the chosen element in the result array
        v[i] = element_type(m) ;
        ++i ;

        // Account for the contribution of this element by updating the remainder
        remainder -= contribution ;

        // Require subsequent elements to have larger values
        m_first = m + 1 ;

      }

      // This loop does double duty for handling the i==k-1 term and the remainder==0 break
      while (i < k)
      {
        v[i] = element_type(n - remainder + i - k) ;
        ++i ;
      }
      return v ;
    }
  }
}

#include <iostream>

int main()
{
    auto prbs = LTE_COMMON::combinatorial::subset_from_index_incremental(100, 4, 3921224);
    for(auto const& prb : prbs) { std::cout << prb << ' '; }
    std::cout << std::endl;

    std::vector<int> v{44, 45, 46, 47};
    std::cout << LTE_COMMON::combinatorial::combinatorial_index_unsorted(100, v) << std::endl;
}
