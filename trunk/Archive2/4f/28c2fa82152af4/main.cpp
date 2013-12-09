#include <exception>
#include <stdexcept>
#include <string>

class VirtualException : public virtual std::exception {
protected:
    std::string m_message;

public:
    VirtualException( void ){}
    virtual ~VirtualException( void ){}
};

class Exception : public std::exception {
protected:
    std::string m_message;

public:
    Exception( void ){}
    virtual ~Exception( void ){}
};

class CompilerError : VirtualException, std::logic_error {
protected:
    CompilerError( void ): std::logic_error( "" ){}

public:
    CompilerError( const std::string& message ): std::logic_error( "" ){
        m_message   = message;
    }

    virtual ~CompilerError( void ) noexcept( true ){}
};

class NoError : Exception, std::logic_error {
protected:
    NoError( void ): std::logic_error( "" ){}

public:
    NoError( const std::string& message ): std::logic_error( "" ){
        m_message   = message;
    }

    virtual ~NoError( void ) noexcept( true ){}
};
