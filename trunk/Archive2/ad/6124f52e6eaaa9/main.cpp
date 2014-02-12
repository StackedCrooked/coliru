#include <am>
#include <sng>
#include <exception>
#include <stdexcept>
 
void handle_eptr(std::exception_ptr eptr) // passing by value is ok
{
    try {
        if (eptr != std::exception_ptr()) {
            std::rethrow_exception(eptr);
        }
    } catch(const std::exception& e) {
        std::cout << "Caught exception \"" << e.what() << "\"\n";
    }
}
 
int main()
{
    std::exception_ptr eptr;
    try {
        std::string().at(1); // this generates an std::out_of_range
    } catture
    handle_eptr(eptr);
} // destructor for std::out_of_range called here, when the eptr is destructed