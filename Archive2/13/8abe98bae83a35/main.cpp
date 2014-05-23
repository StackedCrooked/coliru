#include <system_error>
#include <iostream>

enum Errors {
    ONE,
    TWO,
    THREE,
};

enum SUB_Errors {
    NOERROR,
    ERROR1  = 0xff,
    ERROR2  = 0xfff,
    ERROR3  = 0xffff, 
};

// specialize
namespace std {
    template<>
        struct is_error_condition_enum<Errors> : public std::true_type {};
    template<>
        struct is_error_code_enum<Errors> : public std::true_type {};
}

// Test error_category
class TestCategory : public std::error_category { 
    public:
        virtual ~TestCategory()
        { }

        virtual const char* name() const noexcept
        {
            return "Test Error";
        }

        virtual std::string message(int val) const noexcept
        {
            switch(val)
            {
                case NOERROR: return "Success";
                case ERROR1:  return "ERROR1";
                case ERROR2:  return "ERROR2";
                case ERROR3:  return "ERROR3";
                default:      return "Unhandled Error";
            };
        }
};

// Test error_condition
class TestCondition : public std::error_condition {
    private:
        int error;
        std::error_category const & cat;

    public:
        int value() const { return error; }
        std::error_category const & category() const { return cat; }

    public:
        TestCondition(int suberror, std::error_category const & category) noexcept :
            std::error_condition(suberror, category),
            error(suberror),
            cat(category)
        { }

        TestCondition(std::error_condition const & err) noexcept :
            std::error_condition(err.value(), err.category()),
            error(err.value()),
            cat(err.category())
        { }

        TestCondition(TestCondition const& other) :
            error(other.error),
            cat(std::move(other.cat))
        { }

        virtual ~TestCondition() { }
};

std::ostream& operator<<(std::ostream &o, std::error_condition &err) {
    o << err.category().name() << ": " << err.category().message(err.value());
    return o;
}

std::ostream& operator<<(std::ostream &o, std::error_condition const &err) {
    o << err.category().name() << ": " << err.category().message(err.value());
    return o;
}

std::error_condition returnTest(int x) {
    // if TestCategory is non-temporary, this works.
    if (x == 0)
        return TestCondition{NOERROR, TestCategory()};
    return TestCondition{ERROR1, TestCategory()};
}

int main(void) 
{
    TestCondition te(NOERROR, TestCategory());
    std::cout << te << std::endl;

    // segfault
    std::cout << returnTest(1) << std::endl;
}
