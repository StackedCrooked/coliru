template <class Type> class product {};
template <> class product<double> { public: typedef double type; };

template<class Type> class product2 { 
    public: typedef typename product<Type>::type type; 
};

//------------

namespace N1 {

template <class Cmpt> class Tensor {  };

template <class Cmpt> 
typename product2<Cmpt>::type operator& 
(const Tensor<Cmpt>& a, const Tensor<Cmpt>& b) 
{ return 0; }         // [1]

template <class Cmpt> 
typename product<Cmpt>::type operator& 
(const Tensor<Cmpt>& a, const Tensor<Cmpt>& b) 
{ return 0; }

} // ::N

//-----

namespace N2 {

template<class Type> class fvMatrix;

template<class Type>
fvMatrix<Type> operator& 
(const fvMatrix<Type>& a, const fvMatrix<Type>& b) 
{ return a; }

template <class Type> class fvMatrix {
    friend fvMatrix<Type> operator& <Type> 
    (const fvMatrix<Type>& a, const fvMatrix<Type>& b);
};

} // ::N2

//----------

int main() {
  N2::fvMatrix<int> m;
  m & m;
  return 0;
}