#include <iostream>
#include <vector>
#include <iterator>

template<class T>
struct Void {
  typedef void type;
};

template<class T, class U = void>
struct has_container_type : public std::false_type {
    
};

template<class T>
struct has_container_type<T, typename Void<typename T::container_type>::type > : public std::true_type {
    
};

template<typename It>
void f ( It begin, std::false_type has_container ) {
    typedef typename It::value_type value_type;
    std::cout << "Iterator value_type " << sizeof(value_type);
}

template<typename It>
void f ( It begin, std::true_type has_container ) {
    typedef typename It::container_type::value_type value_type;
    std::cout << "Container value_type " << sizeof(value_type);
}

template<typename It>
void f ( It begin ) {
    typedef typename has_container_type<It>::type has_type;
    f( begin, has_type() );
}

int main() {
    std::vector<int> v = {1,2,3,4,5,6,7,8};
    f( std::back_inserter( v ) );
    std::cout << '\n';
    f( std::begin( v ) );
}