    #include <iostream>
    #include <map>
    #include <utility>
    #include <string>
    #include <type_traits>
    
    template <typename T>
    struct to_value
    {
        typedef typename std::remove_const< typename std::remove_reference<T>::type >::type type;
    };
    
    template <typename T>
    struct executioner {
        inline static void exec( const T & ){
        std::cout << "generic" << std::endl;
        }
    };
    
    template <typename T1, typename T2>
    struct executioner<std::pair<T1, T2> > {
        inline static void exec( const std::pair<T1, T2>& t ){
    	std::cout << "pair" << std::endl;
    	executioner<T1>::exec( t.first );
    	executioner<T2>::exec( t.second );
        }
    };
    
    template <template <typename ...> class Container,
    	  typename ... Ts>
    struct executioner<Container<Ts ...> > {
        inline static void exec( const Container<Ts ...> & c ){
    	std::cout << "cont" << std::endl;
    	auto it = c.begin();

        typedef decltype( *it ) ContainedType;
    	executioner< typename to_value<ContainedType>::type >::exec( * it );
        }
    };
    
    template <typename T> void execute( const T & t ){
        executioner<T>::exec( t );
    }
    
    int main(){
        std::map<int,std::string> aMap = { { 0, "zero" }, { 1, "one" }, { 2, "two" } };
        execute( aMap );
    }