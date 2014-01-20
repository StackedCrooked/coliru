#include <iostream>

#include <boost/mpl/set.hpp>
#include <boost/mpl/for_each.hpp>

struct Param {};
struct Base {
        virtual char f(Param const &) const = 0;
};
struct A : Base {
        A(){}       //Apparently mpl::for_each (or maybe the way I'm using it) requires that the types be default constructible
        explicit A(Param const &) {}
        virtual char f(Param const &) const {return 'A';}
};
struct B : Base {
        B(){}
        explicit B(Param const &) {}
        virtual char f(Param const &) const {return 'B';}
};
struct C : Base {
        C(){}
        explicit C(Param const &) {}
        virtual char f(Param const &) const {return 'C';}
};

struct f_caller 
{
    char& result;
    bool& end;

    const Param& param;
    const Base& base;
    
    f_caller(char& result_, bool& end_, const Param& param_, const Base& base_):result(result_),end(end_),param(param_),base(base_){};
    
    template <typename Type>
    void operator()(const Type&) const
    {
        if(!end)    //This is awful, maybe there is a better algorithm than mpl::for_each, but I'm no expert
        {
            Type const * const p = dynamic_cast<Type const *>(&base);
            if(p)
            {
                end=true;
                result=p->f(param);
            }
        }
    }
};

template <typename Sequence>
char my_function(Param const & param, Base const & base)
{
        char result='0';
        bool end=false;
        
        boost::mpl::for_each<Sequence>(f_caller(result,end,param,base));
        
        return result;
}

int main()
{
    Param x,y;
    std::cout << my_function<boost::mpl::set<A, B, C> >(x, A(y)) << std::endl;
    std::cout << my_function<boost::mpl::set<A, C> >(x, B(y)) << std::endl;
}