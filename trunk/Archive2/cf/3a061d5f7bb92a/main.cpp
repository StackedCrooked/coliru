#include<vector>
#include<functional>
#include<iostream>

int foo() {
    std::cout << "Executing " << __func__ << std::endl;
    return 0;
}

int bar(float a) {
    std::cout << "Executing " << __func__ << std::endl;
    return 1;
}

struct foobar {
    int operator()() {
      std::cout << "Executing " << __func__ << std::endl;
      return 0;        
    }
};

/**
 * @brief Executes a chain of calls in the same order they were registered.
 * Stops if some of the call returns an error.
 */
class ChainOfCallsHandler {
public:
   using callback_type = std::function< int ()>;
   
   ChainOfCallsHandler(int success ) : m_success_value(success) {}
   
   ChainOfCallsHandler& operator()(callback_type f) {
       m_list.push_back( f );
       return *this;
   }
   
   int execute() {
       int result = m_success_value;
       for(auto& x : m_list) {
           result = x();
           if ( result != m_success_value) break;
       }
       return result;
   }
   
   
private:   
   int m_success_value;
   std::vector< callback_type > m_list;
};

inline ChainOfCallsHandler chain_calls_with_success_value(int success_value) {
    return ChainOfCallsHandler(success_value);
}

int main() {

    auto handler = chain_calls_with_success_value(0)
    ( foo )
    ( [](){ return bar(1.0); } )
    ( foobar() );
    
    std::cout << handler.execute() << std::endl;
    return 0;
}