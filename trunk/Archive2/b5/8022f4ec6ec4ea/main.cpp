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

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

using namespace std;



//ADDED FORWARD DECLARATION
template <typename T>
void serialize(boost::archive::text_oarchive &oa, const T& v);

namespace simple
{
    template<typename T> 
    struct serialize{};
    
    template<> 
    struct serialize<int>
    {
        static void write(boost::archive::text_oarchive &oa, int v) { oa << v ;}
    };
    
    template<> //CHANGED THIS TO DOUBLE
    struct serialize<double>
    {
        static void write(boost::archive::text_oarchive &oa, double v) { oa << v ;  }
    };
    
    template<> 
    struct serialize<std::string>
    {
    	static void write(boost::archive::text_oarchive &oa, const std::string& v){ oa << v ;  }
    };
     
}


struct serial_out
{
	boost::archive::text_oarchive &oa;

	serial_out(boost::archive::text_oarchive &oa_) : oa(oa_) {}

    template< typename T > //ADDED CONST
    void operator() (const T & v , typename std::enable_if<!boost::fusion::traits::is_sequence<T>::value>::type* = 0 ) const
    { 
        simple::serialize<T>::write(oa, v); 
    }
    
    template< typename T > //ADDED CONST
    void operator() (const T & v , typename std::enable_if<boost::fusion::traits::is_sequence<T>::value>::type* = 0  ) const
    { 
        serialize(oa, v); 
    }
    
    template< typename Class, int N, bool Const > 
    void operator() (const boost::fusion::extension::adt_attribute_proxy<Class,N,Const>& v , typename std::enable_if<!boost::fusion::traits::is_sequence<typename boost::fusion::result_of::value_at_c<Class,N>::type>::value>::type* = 0 ) const
    { 
        (*this)(v.get()); 
    }
    
    template< typename Class, int N, bool Const > 
    void operator() (const boost::fusion::extension::adt_attribute_proxy<Class,N,Const>& v , typename std::enable_if<boost::fusion::traits::is_sequence<typename boost::fusion::result_of::value_at_c<Class,N>::type>::value>::type* = 0 ) const
    { 
        serialize(oa, v.get()); 
    }
    
    template< typename T >
    void operator()( const std::vector<T> & v ) const
    {
        simple::serialize<int>::write(oa, v.size());
        std::for_each(v.begin(),v.end(),*this);
    }
    
    template< typename T >
    void operator()( const std::list<T> & v ) const
    {
        simple::serialize<int>::write(oa, v.size());
        std::for_each(v.begin(),v.end(),*this);
    }
};

//REORDERED
template< typename T >
void serialize(boost::archive::text_oarchive &oa, const T& v)
{
	boost::fusion::for_each( v, (serial_out(oa)) );
}
//////////////////////////////////////////////////////////////////

//ADDED FORWARD DECLARATION
template <typename T>
void de_serialize(boost::archive::text_iarchive &ia, T& v);

namespace simple
{
    template<typename T> 
    struct de_serialize{};
    
    template<> 
    struct de_serialize<int>
    {
		static void read(boost::archive::text_iarchive &ia, int &v) { ia >> v ; }
    };
    
    template<> //CHANGED THIS TO DOUBLE
    struct de_serialize<double>
    {
        static void read(boost::archive::text_iarchive &ia, double &v) { ia >> v ; }
    };
    
    template<> 
    struct de_serialize<std::string>
    {
		static void read(boost::archive::text_iarchive &ia, std::string& v){ ia >> v ; }
    };


}


struct serial_in
{
	boost::archive::text_iarchive &ia;
	serial_in(boost::archive::text_iarchive &ia_):ia(ia_) {}

    template< typename T > 
    void operator() (T & v , typename std::enable_if<!boost::fusion::traits::is_sequence<T>::value>::type* = 0 ) const
    { 
        simple::de_serialize<T>::read(ia, v); 
    }
    
    template< typename T > 
    void operator() (T & v , typename std::enable_if<boost::fusion::traits::is_sequence<T>::value>::type* = 0  ) const
    { 
        de_serialize(ia, v); 
    }
    
    template< typename Class, int N, bool Const > 
    void operator() (const boost::fusion::extension::adt_attribute_proxy<Class,N,Const>& v , typename std::enable_if<!boost::fusion::traits::is_sequence<typename boost::fusion::result_of::value_at_c<Class,N>::type>::value>::type* = 0 ) const
    { 
		(*this)(v.get());
	}
    
    template< typename Class, int N, bool Const > 
    void operator() (const boost::fusion::extension::adt_attribute_proxy<Class,N,Const>& v , typename std::enable_if<boost::fusion::traits::is_sequence<typename boost::fusion::result_of::value_at_c<Class,N>::type>::value>::type* = 0 ) const
    { 
		de_serialize(ia, v.get()); 
	}
    
    template< typename type_t >
    void operator()( std::vector<type_t> & v ) const
    {
        int vector_size = 0;
		type_t value_;

		simple::de_serialize<int>::read(ia, vector_size);
		v.reserve(vector_size);

		for(auto i=0;i<vector_size;++i)
		{
			(*this)(value_); //CHANGED
			v.push_back(value_);
		}
    }
    
    template< typename T >
    void operator()( std::list<T> & v ) const
    {
    }
};

//REORDERED
template< typename T >
void de_serialize(boost::archive::text_iarchive &ia, T& v)
{
    boost::fusion::for_each( v, (serial_in(ia)) );
}
//////////////////////////////////////////////////////////////////



class secret_point
{
    public:
    secret_point(double x, double y) : x_(x), y_(y) {}
	secret_point() : x_(0), y_(0) {}
    double& get_x() { return x_; }
    const double& get_x() const { return x_; }
    void set_x(double d) { x_=d; }
    double& get_y() { return y_; }
    const double& get_y() const { return y_; }
    void set_y(double d) { y_=d; }
    private:
    double x_, y_;
};

//ADDED ANOTHER CLASS
class points
{
    public:
    points() {}
    std::vector<secret_point>& get_sp(void) {return p;}
    const std::vector<secret_point>& get_sp(void) const {return p;}
    void set_sp(std::vector<secret_point> x) { p = x ;}
    private:
    std::vector<secret_point> p;
};

//I'VE HAD TO CHANGE THE RETURN TYPES TO REFERENCES TO MAKE IT WORK, NOT SURE IF IT WILL PRESENT ANY PROBLEMS
BOOST_FUSION_ADAPT_ADT( secret_point, (double&, const double&, obj.get_x(), obj.set_x(val) ) (double&, const double&, obj.get_y(), obj.set_y(val) ) )
BOOST_FUSION_ADAPT_ADT( points,  (std::vector<secret_point>&, const std::vector<secret_point>&, obj.get_sp(), obj.set_sp(val) ) )

int main(int argc, char *argv[]) 
{
    secret_point p(12,34);
    secret_point q(56,78);
    
    std::vector<secret_point> x;
    x.push_back(p);
    x.push_back(q);
    
    points  ps, po;
    ps.set_sp(x);
    
	std::ostringstream os;
	boost::archive::text_oarchive oa(os);

    serialize(oa, ps);
	std::cout << os.str() << std::endl;

	std::istringstream is(os.str());
	boost::archive::text_iarchive ia(is);

	de_serialize(ia, po);
    
    std::ostringstream os2;
    boost::archive::text_oarchive oa2(os2);
    
    serialize(oa2, po);
    std::cout << os2.str() << std::endl;


    return 0;
}