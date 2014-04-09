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

//ADDED FORWARD DECLARATION
template <typename T>
void serialize(const T& v);

namespace simple
{
    template<typename T> 
    struct serialize{};
    
    template<> 
    struct serialize<int>
    {
        static void write(int v) { cout << v << endl; }
    };
    
    template<> //CHANGED THIS TO DOUBLE
    struct serialize<double>
    {
        static void write(double v) { cout << v << endl;  }
    };
    
    template<> 
    struct serialize<std::string>
    {
        static void write(const std::string& v)
        {
            cout << v << endl; 
        }
    };
    
    
    
    //ADDED SPECIALIZATION FOR ADT_ATTRIBUTE_PROXY
    template<typename Class,int N,bool DontCare> 
    struct serialize<boost::fusion::extension::adt_attribute_proxy<Class,N,DontCare> >
    {
        static void write_impl(const boost::fusion::extension::adt_attribute_proxy<Class,N,DontCare>& val, boost::mpl::false_)
        {
            //using "result_of::value_at_c" seems to work, I don't know if it's the only way or the best way
            serialize< typename boost::fusion::result_of::value_at_c<Class,N>::type >::write(val);
        }
        
        static void write_impl(const boost::fusion::extension::adt_attribute_proxy<Class,N,DontCare>& val, boost::mpl::true_)
        {
            //using "result_of::value_at_c" seems to work, I don't know if it's the only way or the best way
            ::serialize< typename boost::fusion::result_of::value_at_c<Class,N>::type >(val);
        }
        
        static void write(const boost::fusion::extension::adt_attribute_proxy<Class,N,DontCare>& val)
        {
            write_impl(val,typename boost::fusion::traits::is_sequence<typename boost::fusion::result_of::value_at_c<Class,N>::type>::type());
        }
    };
}


struct serial_out
{
    template< typename T > //ADDED CONST
    void operator() (const T & v , typename std::enable_if<!boost::fusion::traits::is_sequence<T>::value>::type* = 0 ) const
    { 
        simple::serialize<T>::write(v); 
    }
    
    template< typename T > //ADDED CONST
    void operator() (const T & v , typename std::enable_if<boost::fusion::traits::is_sequence<T>::value>::type* = 0  ) const
    { 
        serialize(v); 
    }
    
    template< typename T >
    void operator()( const std::vector<T> & v ) const
    {
        simple::serialize<int>::write(v.size());
        std::for_each(v.begin(),v.end(),*this);
    }
    
    template< typename T >
    void operator()( const std::list<T> & v ) const
    {
        simple::serialize<int>::write(v.size());
        std::for_each(v.begin(),v.end(),*this);
    }
};

//REORDERED
template< typename T >
void serialize(const T& v)
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

//ADDED ANOTHER CLASS
class points
{
    public:
    points(secret_point x):p(x) {}
    secret_point get_sp(void) const {return p;}
    void set_sp(secret_point x) { p = x ;}
    private:
    secret_point p;
};

BOOST_FUSION_ADAPT_ADT( secret_point, (double, double, obj.get_x(), obj.set_x(val) ) (double, double, obj.get_y(), obj.set_y(val) ) )
BOOST_FUSION_ADAPT_ADT( points,  (secret_point, secret_point, obj.get_sp(), obj.set_sp(val) ) )

int main(int argc, char *argv[]) 
{
    secret_point p(12,34);
    
    points  ps(p);
    //vector<secret_point> v;
    //v.emplace_back(123,456);
    //v.emplace_back(789,123);
    
    //boost::fusion::vector<secret_point, std::vector<secret_point> > fv(p,v);
    serialize(p);
    
    //ADDED serialization for another class 
    serialize(ps);
    
    return 0;
}