#include <exception>
namespace Structures {
class ListIndexOutOfBoundsException: public ::std::exception {
public:
    ListIndexOutOfBoundsException(int index, int length);
    virtual const char* what() const noexcept;
    virtual ~ListIndexOutOfBoundsException() noexcept;
private:
    const char* errorString;
};
}

#include <string>
#include <sstream>
#include <iostream>
namespace Structures {
using ::std::stringstream;

ListIndexOutOfBoundsException::ListIndexOutOfBoundsException(int index,int length) {
     errorString = (std::string("List index (")
        + std::to_string(index) + std::string(") out of bounds! (list length: ")
        + std::to_string(length) + std::string(")")).c_str();
}

const char* ListIndexOutOfBoundsException::what() const noexcept {
    return errorString;
}

ListIndexOutOfBoundsException::~ListIndexOutOfBoundsException() noexcept {

}


}

int main() {
    try {
        throw Structures::ListIndexOutOfBoundsException(0, 10);
    } catch (Structures::ListIndexOutOfBoundsException& ex) {
        std::cout << ex.what() << std::endl;
    }
}