#include <stdexcept>
#include <string>
#include <memory>

class BaseException : public virtual std::exception {
public:
    explicit BaseException(const std::string& msg) : msg_storage(new std::string(msg)) { }
    explicit BaseException(const char* msg) : msg_storage(new std::string(msg)) { }
    
    virtual const char* what() const noexcept { return msg_storage->c_str(); }
    
private:
    std::shared_ptr<std::string> msg_storage;
};


int main(int argc, char **argv) {
    throw BaseException("computation aborted with answer: 42");
    
    return 0;
}
