#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>

        enum class MessageLevel { info, exception };

        template<MessageLevel L>
        class MessageStream
        {
            std::ostringstream ss;
            static unsigned counter;
            std::string message() const;
        public:
            ~MessageStream( ); // noexcept(false);

            static unsigned get_counter() { return counter; }

            template<class T>
            MessageStream& operator<< (const T& t) { ss << t; return *this; }
        };

        template<MessageLevel L>
        unsigned MessageStream<L>::counter = 0;

        //-------------------------------------------------------------------------
        // exlicit template instantiations
        //-------------------------------------------------------------------------
        template<MessageLevel L>
        std::string MessageStream<L>::message() const { return ss.str(); }

        template<> MessageStream<MessageLevel::info>::~MessageStream() //noexcept(false)
        { std::cout << message(); ++counter; }

        template<> MessageStream<MessageLevel::exception>::~MessageStream( ) noexcept(false) // [[noreturn]]
        {
            ++counter;
            if(std::current_exception())
                std::throw_with_nested(std::runtime_error(ss.str()));
            else
                throw std::runtime_error( ss.str( ) );
        }

        using Info = MessageStream<MessageLevel::info>;
        using Throw = MessageStream<MessageLevel::exception>;


int main() try
{
    Info() << "info message\n";
    Throw() << "exception thrown";
}
catch(std::exception& e)
{
    std::cerr << e.what();
}
