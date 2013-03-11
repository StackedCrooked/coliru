#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/phoenix.hpp>
#include <boost/spirit/home/support/context.hpp>

class Object {
    public:
        void initialize(std::vector<int>) { }
        void frobnicate(int) { }
};

int main() {
    using boost::phoenix::bind;
    using boost::spirit::_val;
    using boost::spirit::_1;

    std::cout << "------------\n";
    std::cout << typeid ( bind                 ( &Object::initialize , *boost::spirit::_val , boost::spirit::_1)).name ( ) << '\n';
    std::cout << typeid ( bind                 ( &Object::initialize ,  boost::spirit::_val , boost::spirit::_1)).name ( ) << '\n';
    std::cout << "------------\n";
    std::cout << typeid ( bind                 ( &Object::frobnicate , *boost::spirit::_val , boost::spirit::_1)).name ( ) << '\n';
    std::cout << typeid ( bind                 ( &Object::frobnicate ,  boost::spirit::_val , boost::spirit::_1)).name ( ) << '\n';
    std::cout << "------------\n";
    std::cout << typeid ( bind                 ( &Object::initialize , *boost::spirit::_val , boost::spirit::_1)).name ( ) << '\n';
    std::cout << typeid ( std::bind            ( &Object::initialize , *boost::spirit::_val , boost::spirit::_1)).name ( ) << '\n';
    std::cout << typeid ( boost::phoenix::bind ( &Object::initialize , *boost::spirit::_val , boost::spirit::_1)).name ( ) << '\n';
    std::cout << "------------\n";
    std::cout << typeid ( bind                 ( &Object::frobnicate , *boost::spirit::_val , boost::spirit::_1)).name ( ) << '\n';
    std::cout << typeid ( std::bind            ( &Object::frobnicate , *boost::spirit::_val , boost::spirit::_1)).name ( ) << '\n';
    std::cout << typeid ( boost::phoenix::bind ( &Object::frobnicate , *boost::spirit::_val , boost::spirit::_1)).name ( ) << '\n';
    std::cout << "------------\n";
}
