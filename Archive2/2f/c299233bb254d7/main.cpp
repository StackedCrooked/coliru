#include <boost/shared_ptr.hpp>
#include <iostream>

class BasicLogger {
  public:
    virtual ~BasicLogger() { std::cout << __PRETTY_FUNCTION__ << "\n"; }
//...
};

    class Logger : BasicLogger {
    public:
        static boost::shared_ptr<Logger>& getLog() { 
            static boost::shared_ptr<Logger> log_;

            if (!log_) {
                log_.reset(new Logger());
            }

            return log_;
        };
        static BasicLogger &log(const std::string &key){
            return (*getLog())(key);//calls operator()
        }
        virtual BasicLogger & operator()(const std::string &key) {
            std::cout << "called: " << key << "\n";
            return *this;
        }
        virtual ~Logger() {}
    };


int main()
{
    {
        BasicLogger& csv = Logger::log("trip.csv");
    }
}
