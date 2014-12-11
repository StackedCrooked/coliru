#include <iostream>
#include <boost/system/error_code.hpp>

enum myerrc { success = 0, war, famine, death, pestilence };

namespace boost
{
    namespace system
    {
        //tells boost that a random enum type is actually an error code enum
        template<> struct is_error_code_enum<myerrc> { static const bool value = true; };
    }
}


class mycategory_t : public boost::system::error_category
{
  public:
    const char* name() const BOOST_SYSTEM_NOEXCEPT
    {
        return "The errors";
    }
    
    std::string message(int ev) const
    {
        switch((myerrc)ev)
        {
            case success    : return "success";
            case war        : return "war";
            case famine     : return "famine";
            case death      : return "death";
            case pestilence : return "pestilence";
        }
        return "wtf?";
    }
        
} mycategory;

//allows boost to instantiate an error_code with the correct category
//based on the type of the error enum
boost::system::error_code make_error_code(myerrc val)
{
    return boost::system::error_code(val, mycategory);
}

int main(int argc, char* argv[])
{
    boost::system::error_code err(famine, mycategory);
    std::cout << std::boolalpha << (err == success) << std::endl
                                << (err == famine)  << std::endl;
}
