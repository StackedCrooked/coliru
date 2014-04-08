#include <iostream>
#include <typeinfo>
#include <string>
#include <boost/fusion/include/sequence.hpp>
#include <boost/fusion/include/algorithm.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/adapt_adt.hpp>
#include <boost/fusion/include/is_sequence.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/type_traits.hpp> 

#include <vector>
#include <list>

using namespace std;

template <typename T >
void serialize(T v);

namespace simple
{
template<typename T> struct serialize{};
template<> struct serialize<int>
{
    static void write(int v) { cout << v << endl; }
};
template<> struct serialize<double>
{
    static void write(double v) { cout << v << endl;  }
};
template<> struct serialize<std::string>
{
    static void write(const std::string& v)
    {
        cout << v << endl; 
    }
};

template<typename Class,int N,bool NoIdea> struct serialize<boost::fusion::extension::adt_attribute_proxy<Class,N,NoIdea> >
{
    static void write(const boost::fusion::extension::adt_attribute_proxy<Class,N,NoIdea>& val)
        {
            serialize< typename boost::fusion::result_of::value_at_c<Class,N>::type >::write(val);
        }
};
}


struct serial_out
{
template< typename T > 
void operator() (const T & v , typename std::enable_if<!boost::fusion::traits::is_sequence<T>::value>::type* = 0 ) const
{ 
    simple::serialize<T>::write(v); 
}

template< typename T > 
void operator() (const T & v , typename std::enable_if<boost::fusion::traits::is_sequence<T>::value>::type* = 0  ) const
{ 
    serialize(v); 
}

template< typename T >
void operator()( std::vector<T> & v ) const
{
    simple::serialize<int>::write(v.size());
    std::for_each(v.begin(),v.end(),*this);
}

template< typename T >
void operator()( std::list<T> & v ) const
{
    simple::serialize<int>::write(v.size());
    std::for_each(v.begin(),v.end(),*this);
}
};

template< typename T >
void serialize(T v)
{
boost::fusion::for_each( v, (serial_out()) );
}




class secret_point
{
public:
secret_point(double x, double y) : x_(x), y_(y) {}
double get_x() const { return x_; }
void set_x(double d) { x_=d; }
double get_y() const { return y_; }
void set_y(double d) { y_=d; }
private:
double x_, y_;
};

BOOST_FUSION_ADAPT_ADT( secret_point, (double, double, obj.get_x(), obj.set_x(val) ) (double, double, obj.get_y(), obj.set_y(val) ) )

int main(int argc, char *argv[]) 
{
secret_point p(112,233);
serialize(p);

return 0;
}