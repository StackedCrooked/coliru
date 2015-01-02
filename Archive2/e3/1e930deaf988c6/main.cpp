#include <iostream>
#include <string>
#include <cassert>
#include <system_error>

//////////////////////// Err enum
enum class TestErr : unsigned int
{
    NONE, ONE, TWO, THREE, LAST
};

const char * TestMsgs[] = 
{
    "NONE", "ONE", "TWO", "THREE",  
};


//////////////////////// Error category
class TestCategory : public std::error_category
{
public:
    TestCategory() noexcept
    { }
    
    virtual ~TestCategory()
    { }
    
    virtual const char * name() const noexcept
    {
        return "TestError";
    }
    
    virtual std::string message(int val) const noexcept
    {
        // sloppy
        return TestMsgs[static_cast<unsigned int>(val)];
    }
};

//// Getter for category
const std::error_category& test_category() noexcept
{
    static TestCategory _tc{};
    return _tc;
}

/////////////////////////// std extensions
namespace std
{
    template<> struct is_error_condition_enum<TestErr>: public true_type {};
    error_condition make_error_condition(TestErr e)
    {
        return error_condition(static_cast<unsigned int>(e), test_category());
    }
}


/////////////////////////// Error class
struct error final : std::error_condition
{
    /* for our enum */
    error(TestErr e = TestErr::NONE) :
        std::error_condition(std::make_error_condition(e))
    {
    }
    
    /* for errno */
    error(std::errc _errno) noexcept:
        std::error_condition(std::make_error_condition(_errno))
    { 
    }
    
    error& operator=(TestErr e) noexcept
    {
        assign(static_cast<unsigned int>(e), category());
        return *this;
    }

    friend std::basic_ostream<char>& operator<<(std::basic_ostream<char> & o, error const & e)
    {
        o <<  e.category().name() << ": " << e.message();
        return o;
    }
};




/////////////////// Implementing object
class Foo
{
private:
    int x;
    error m_last_error;
    
public:
    Foo(int x) :
        x(x),
        m_last_error()
    {
        if (x < 10)
        {
            m_last_error = TestErr::ONE;
        }
    }
    
    error const & get_last_error() const
    { return m_last_error; }
};



int main(void)
{
    //// FOO object
    Foo f1{9};
    
    if (auto err = f1.get_last_error()) 
    {
        std::cout << err << std::endl;
    }
    
    //// FOO object
    Foo f2{9};

    if (auto err = f2.get_last_error()) 
    {
        std::cout << err << std::endl;
    }
}
