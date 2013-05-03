#include <boost/exception/all.hpp>

struct my_exception4: std::exception, boost::exception {
    mutable bool in_what = false;
    mutable std::string mWhat;
    
    virtual const char* what() const throw() {
        if (mWhat.size() == 0) {
            struct g { 
                bool &b; 
                ~g() { 
                    b = false; 
                } 
            } guard{in_what};
            if (in_what) {
                return "(empty)";
            } else {
                in_what = true;
                mWhat += boost::diagnostic_information(*this);
            }
        }
        return mWhat.c_str();
    }
};


int main() {
    try {
        BOOST_THROW_EXCEPTION(my_exception4());
    } catch (const std::exception& e){
        std::cout << e.what() << std::endl;
    }
}