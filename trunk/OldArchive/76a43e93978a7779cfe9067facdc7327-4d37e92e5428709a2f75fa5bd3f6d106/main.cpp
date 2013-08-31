#include <iostream>

#include <boost/type_erasure/any.hpp>
#include <boost/type_erasure/any_cast.hpp>
#include <boost/type_erasure/builtin.hpp>
#include <boost/type_erasure/operators.hpp>
#include <boost/type_erasure/member.hpp>
#include <boost/type_erasure/free.hpp>
#include <boost/mpl/vector.hpp>

using namespace std;
namespace mpl = boost::mpl;
using namespace boost::type_erasure;

class Foo
{
    public:

        template <class T>
        void templateFunction(T t)
        {
            cout << t << endl;
        }
};

template<class C, class T>
struct has_template_function
{
    static void apply(C& cont, const T& arg) { cont.templateFunction(arg); }
};

namespace boost
{
    namespace type_erasure
    {
        // template<class C, class T, class Base>
        // struct concept_interface<has_template_function<C, T>, Base, C> : Base
        // {
            // void templateFunction(typename as_param<Base, const T&>::type arg)
            // { call(has_template_function<C, T>(), *this, arg); }
        // };
    	
		template<class T, class U, class Base, class Enable>
		struct concept_interface< has_template_function<T, U>, Base, T, Enable> : Base
		{
			typedef void _fun_defined;
			void templateFunction(typename as_param<Base, const U&>::type arg)
			{
				call(::has_template_function<T, U>(), *this, arg);
			}
		};

		template<class T, class U, class Base>
		struct concept_interface< has_template_function<T, U>, Base, T, typename Base::_fun_defined> : Base
		{
			using Base::templateFunction;
			void templateFunction(typename as_param<Base, const U&>::type arg)
			{
				call(::has_template_function<T, U>(), *this, arg);
			}
		};
    }
}

//c++11 only
//template <typename...T>
//using any_with_template = any<boost::mpl::vector<has_template_function<_self, T>...>, _self&>;

int main()
{
	
	Foo foo;
    any<boost::mpl::vector<has_template_function<_self, double>, has_template_function<_self, int>, has_template_function<_self,const char*> > , _self&> c = foo;
	//any_with_template<double,int,const char*> c = foo; //c++11 only
    
    c.templateFunction(5);

    c.templateFunction(6.8);
	
	c.templateFunction("Hello");

    return 0;
}