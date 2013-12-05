#include <iostream>

#include <array>
#include <ostream>
 
namespace ffa
{
  namespace monomial
  {
    namespace policy
    {
      template <typename T, T C, T D, T R>
      class Array
        : private std::array<T, D>
      {
      public:
        using MyBase = std::array<T, D>;
        using MyBase::back;
 
        explicit
          Array();
 
        operator
          T()
          const;
 
      protected:
 
        virtual void
          print
          ( std::ostream& stream )
          const;
 
      private:
 
        template <typename TT, TT CC, TT DD, TT RR>
        friend std::ostream&
          operator<<
          ( std::ostream& stream
          , const Array<TT, CC, DD, RR>& array );
 
      };
 
      /////////////////////////////////////////////////////////////////////////
      // Static
      /////////////////////////////////////////////////////////////////////////
 
      /////////////////////////////////////////////////////////////////////////
      // Public
      /////////////////////////////////////////////////////////////////////////
 
      template <typename T, T C, T D, T R>
      Array<T, C, D, R>::Array()
        : std::array<T, D>()
      {
      }
 
      template <typename T, T C, T D, T R>
      Array<T, C, D, R>::operator
        T ()
        const
      {
        T output(back()), power(1);
        for (T i(1); i < D; ++i, power *= C)
        {
          output += (*this)[D-i-1] * power;
        }
        return output;
      }
 
      /////////////////////////////////////////////////////////////////////////
      // Protected
      /////////////////////////////////////////////////////////////////////////
 
      template <typename T, T C, T D, T R>
      void
        Array<T, C, D, R>::print
        ( std::ostream& stream )
        const
      {
        stream << "( ";
        for (T i(0); i < D; ++i)
        {
          stream << (*this)[i] << ' ';
        }
        stream << ")\t" << (T)(*this);
      }
 
      /////////////////////////////////////////////////////////////////////////
      // Private
      /////////////////////////////////////////////////////////////////////////
 
 
      template <typename T, T C, T D, T R>
      std::ostream&
        operator<<
        ( std::ostream& stream
        , const Array<T, C, D, R>& array )
      {
        array.print(stream);
        return stream;
      }
 
    }
  }
}

int main() {
    ffa::monomial::policy::Array<size_t,2,8,285> test;
    
    std::cout << test;
}