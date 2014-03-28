#include <exception>
#include <string>

class BadJumbleException : public std::exception {
public:
    BadJumbleException (const std::string& msg): message(msg) {} // Constructor, accepts a string as the message
    std::string& what() { return message; } // Returns the message string
private:
    std::string message;                         // Stores the exception message
};

int main() {
}