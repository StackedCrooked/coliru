#include <sstream>
#include <string>
#include <exception>

#if _MSC_VER
#define noexcept
#endif

struct CompilerError : std::exception
{
    explicit CompilerError(int code)
    {
        m_stream << "error " << code;
    }

    CompilerError(const CompilerError& rhs)
    {
        std::swap(m_stream, rhs.m_stream);
        std::swap(m_message, rhs.m_message);
    }

    virtual ~CompilerError() noexcept override {}

    virtual const char* what() const noexcept override
    {
        if (m_message.empty())
            m_message = m_stream.str();

        return m_message.c_str();
    }

    CompilerError& operator<<(int x) { m_stream << x; return *this; }
    CompilerError& operator<<(const char* x) { m_stream << x; return *this; }
    CompilerError& operator<<(const std::string& x) { m_stream << x; return *this; }

    mutable std::stringstream m_stream;
    mutable std::string m_message;
};

#include <iostream>

int main()
{
    try
    {
        throw CompilerError(1);
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << '\n';
    }
    
    try
    {
        throw CompilerError(1) << "+" << 2;
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << '\n';
    }
}
