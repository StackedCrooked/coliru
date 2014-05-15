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
   
   void register_function_call(callback_type f) {
       m_list.push_back( f );
   }
   
   int execute() {
       int result = 0;
       for(auto& x : m_list) {
           result = x();
           if ( result != 0) break;
       }
       return result;
   }
private:
   std::vector< callback_type > m_list;
};


int main() {

    ChainOfCallsHandler handler;
    
    handler.register_function_call( foo );
    handler.register_function_call( [](){ return bar(1.0); } );
    handler.register_function_call( foobar() );
    
    std::cout << handler.execute() << std::endl;
    return 0;
}