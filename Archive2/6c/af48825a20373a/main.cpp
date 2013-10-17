#include <iostream>
#include <string>
#include <exception>
#include <stdexcept>
 
 class MyException : public std::exception {
     public:
 };
 
void handle_eptr(std::exception_ptr eptr) // passing by value is ok
{
    try {
        if (eptr != std::exception_ptr()) {
            std::rethrow_exception(eptr);
        }
    } catch(const std::exception& e) {
        std::cout << "Caught exception \"" << e.what() << "\"\n";
    } catch (const MyException &e) {
        std::cout << "Cought my exception\"" << e.what() << "\"\n";
    }
}
 
int main()
{
    std::exception_ptr eptr;
    try {
        // std::string().at(1); // this generates an std::out_of_range
        throw MyException();
    } catch(...) {
        eptr = std::current_exception(); // capture
    }
    handle_eptr(eptr);
} // destructor for std::out_of_range called here, when the eptr is destructed