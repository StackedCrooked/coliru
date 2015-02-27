/*
Want to throw an exception that says "failed to do special thingy because of lowlevel socket error blah blah"
*/
#include <iostream>
#include <system_error>
#include <exception>

int main(int argc, char * argv[])
{
   
   try {
        try {
            try {
                throw std::system_error(EADDRINUSE, std::system_category());
            }
            catch (std::exception& e) {
                std::throw_with_nested(std::runtime_error("failed to bind socket for my special thingy"));
            }
        } catch(std::exception& e) { 
            std::cout << "caught:" << e.what() << "\n"; 
            std::rethrow_if_nested(e); 
        }
    } catch(std::exception& e) { 
        std::cout << "caught again:" << e.what() << "\n";  
    }   
}
