#include <iostream>
#include <string>
#include <vector>


template <class T>
inline const T overloadedMethod(const T& lhs, const T& rhs)
{
    return T(lhs.value+rhs.value);
}

/// \brief AbstractA class
class AbstractA
{
public:
    AbstractA (int aVal):
      value(aVal)
      {}


      inline const AbstractA overloadedMethod(const AbstractA &rhs) const
      {
          return AbstractA(value+rhs.value);            
      }

protected:
    int value;
};

/// \brief A class, deriving from AbstractA,
/// and friending the free-function template.
class A : public AbstractA
{   
    friend const A overloadedMethod<A>(const A& lhs, const A& rhs);
        /// This one gives me compilation error
  //  template<class T> friend const T overloadedMethod(const T& lhs, const T& rhs);
        /// This one would be okay

public:
    A (int aVal):
      AbstractA(aVal)
      {}
};

int main()
{
   A a1(1), a2(2);
   overloadedMethod(a1, a2);

   return 0;
}
