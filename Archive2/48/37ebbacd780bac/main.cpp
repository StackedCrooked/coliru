#include <iostream>
#include <stdexcept>

class ExceptionBase : public std::runtime_error {
public: 
    ExceptionBase( const char * msg ) : std::runtime_error(msg) {}
};

class OperationFailure : virtual public ExceptionBase {
public: 
    using ExceptionBase::ExceptionBase;
protected:
    OperationFailure() : ExceptionBase("") {};
};

class FileDoesNotExistError : virtual public ExceptionBase {
public: 
    using ExceptionBase::ExceptionBase;
protected:
    FileDoesNotExistError() : ExceptionBase("") {};
};

class OperationFailedBecauseFileDoesNotExistError
    : public OperationFailure, FileDoesNotExistError {
public: 
    using ExceptionBase::ExceptionBase;
};

int main() {
    OperationFailedBecauseFileDoesNotExistError e("Hello world!\n");

    std::cout << e.what();
}