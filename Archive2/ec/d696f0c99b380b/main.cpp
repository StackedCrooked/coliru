#include <iterator>
#include <cstddef>
typedef size_t unative_t;
typedef ptrdiff_t native_t;

template <typename T>
class vector
{
public:
  typedef T                                value_type;
  typedef value_type&                      reference;
  typedef const value_type&                const_reference;
  typedef random_access_iterator<T>        iterator;
  typedef random_access_iterator<const T>  const_iterator;
  typedef unative_t                        size_type;
  typedef native_t                         difference_type;
  typedef value_type*                      pointer;
  typedef const value_type*                const_pointer;

  vector(const size_type n = 0) : vector<T>(n, T()) { }

  vector(const size_type n, const T& val) : m_capacity(n == 0 ? 100 : n * 2),
                                        m_size(n), m_data(new T[m_capacity])
  {
    for (decltype(m_size) i = 0; i < m_size; ++i)
      m_data[i] = val;
  }

  // fancy declarations go here...
private:
  size_type m_capacity; // Where size_type is the unsigned word size of the CPU
  size_type m_size;     // for my computer, this is the equivalent of uint64_t.
  pointer m_data;       // At present, pointer is T*
};

//#include "structures/vector.hpp"
#include <vector>

int main()
{
  vector<int> vi;                   // compiles okay
  vector<float> vf(10);             // compiles okay
  vector<double> vd1(100, 30.0);    // compiles okay
  std::vector<double> vd2(100, 30); // compiles okay
  vector<double> vd2(100, 30);      // error: undefined reference to
                                    // vector<double>::vector<int>(int, int)
  return 0;
}