#include <iostream>
#include <memory>
using namespace std;

   template<typename _Tp>     
     struct _MakeUniq                                                           
     { typedef unique_ptr<_Tp> __single_object; };
                                                          
   template<typename _Tp>                   
     struct _MakeUniq<_Tp[]>                
     { typedef unique_ptr<_Tp[]> __array; };
  
    template<typename _Tp, size_t _Bound>
      struct _MakeUniq<_Tp[_Bound]>
      { struct __invalid_type { }; };
                                                                                                                                      
    /// std::make_unique for single objects                                                                                           
    template<typename _Tp, typename... _Args>                                                                                         
      typename _MakeUniq<_Tp>::__single_object                                                                                        
      make_unique(_Args&&... __args)                                                                                                  
      { return unique_ptr<_Tp>(new _Tp(std::forward<_Args>(__args)...)); }                                                            
                                                                                                                                      
    /// std::make_unique for arrays of unknown bound                                                                                  
    template<typename _Tp>                                                                                                            
      typename _MakeUniq<_Tp>::__array                                                                                                
      make_unique(size_t __num)                                                                                                       
      { return unique_ptr<_Tp>(new typename remove_extent<_Tp>::type[__num]()); }                                                     
                                                                                                                                      
    /// Disable std::make_unique for arrays of known bound                                                                            
    template<typename _Tp, typename... _Args>                                                                                         
      typename _MakeUniq<_Tp>::__invalid_type                                                                                         
      make_unique(_Args&&...) = delete;                                                                                               
                                                                                                                                      
  
struct X {
    int a = 1;
};

template <typename X>
struct Y {
	typedef X Base;
	std::unique_ptr<Base> base;
	int b = 2;
};

std::unique_ptr<X> gen_x(std::unique_ptr<X> x)
{
    return std::move(x);
}

template <typename Base>
std::unique_ptr<Y<Base>> gen_y(std::unique_ptr<Base> x)
{
    auto ret = make_unique<Y<Base>>();
    ret->base = std::move(x);
    return std::move(ret);
}

int main() {

    auto x = gen_x(make_unique<X>());
    auto y = gen_y(make_unique<X>());
    
    cout << x->a << endl;
    cout << y->b << endl;
    cout << y->base->a << endl;  // <<------

	return 0;
}