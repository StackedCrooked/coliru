#include <iostream>
#include <utility>
#include <functional>
#include <boost/any.hpp>
#include <vector>
#include <string>
#include <initializer_list>

using boost::any_cast;
template <typename F,typename... T>
using bind_type = decltype(std::bind(std::declval<std::function<F(T...)>>(),std::declval<T>()...));

template <typename F,typename... T>
class Action {
public:

  template <typename... ConstrT>
  Action(std::function<F(T...)> f, ConstrT&&... args)
    : bind_(f,std::forward<ConstrT>(args)...)
  { }

  F act()
  { return bind_(); }

  bind_type<F,T...> bind_;
};


class Results{
public:
    int size;
    std::vector<boost::any> res;
    Results(int n) : size(n) { }
    
    template<typename T>
    T returnit(int i){
        return any_cast<T>(res[i]);
    }
};


class Runner{
private:
    std::vector<boost::any> ACTION_OBJS;
public:
    Runner(const boost::any& a){
        ACTION_OBJS.push_back(a);
    }
    Runner& add_action(const boost::any& a){
        ACTION_OBJS.push_back(a);
        return *this;
    }
    
    /* Does not work for some reason */
    Runner operator=(std::initializer_list<boost::any> a){
        for ( auto& x : a )
            ACTION_OBJS.push_back(x);
        return *this;
    }
    
    
    template <typename F,typename... T>
    void run(Results& r,int start=0){
        for( int i=start; i< ACTION_OBJS.size() && i < r.size ; i++ ){
           auto temp_func = any_cast<Action<F,T...>>(ACTION_OBJS[i]);
           try {
                r.res.push_back( temp_func.act() );
           } catch ( ... ) {
                 r.res.push_back( "Void function" );
            }
        }
    }
    
};




int add (int y , int z){
    return y+z;
}

int mul (int y , int z){
    return y*z;
}

void print(std::string& x){
    std::cout << x << std::endl;    
}

int main()
{
    using AO_Sig1 = Action<int,int,int>;
    using AO_Sig2 = Action<void,std::string&>;
    
    
    AO_Sig1 my_add(add,6, 4);
    AO_Sig1 my_mul(mul,6, 4);
    AO_Sig2 my_print(print,"a_normal_string");
    
    
    Runner r { my_add };
    r.add_action(my_mul);
    r.add_action(my_print);
    
    
    Results res(3);

    

        r.run<int,int,int>(res);

    
        std::cout << res.returnit<int>(0) << std::endl;
        std::cout << res.returnit<int>(1) << std::endl;
        //std::cout << res.returnit<std::string>(2) << std::endl;
    
    //r.add_action(my_mul);
    //r.run<int,int,int>(res,3);
    //std::cout << res.returnit<int>(3) << std::endl;
    
    return 0;
}

