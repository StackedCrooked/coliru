#include <boost/function.hpp>

struct test {
    const char *n;
    int i;

    boost::function<int(void)> read;
    boost::function<void(int)> write;

    test(char const* n, int i, boost::function<int(void)> read, boost::function<void(int)> write) 
        : n(n), i(i), read(read), write(write)
    {}
};

#include <boost/phoenix.hpp>
#include <vector>
using namespace boost::phoenix::arg_names;
namespace phx = boost::phoenix;

namespace mocks {
    static int v;

    typedef std::vector<test> test_t;

    test_t const& tests() {
        static test_t s_tests;
        if (s_tests.empty())
        {
            s_tests.push_back(test ( "test1", 1, phx::val(1), phx::ref(v) = arg1*1 ));
            s_tests.push_back(test ( "test2", 2, phx::val(2), phx::ref(v) = arg1*2 ));
        }

        return s_tests;
    }
}

#include <iostream>

int main() {


    for (mocks::test_t::const_iterator it = mocks::tests().begin();
            it != mocks::tests().end(); ++it)
    {
        test const& test = *it;
        std::cout << "'" << test.n << "'\t" << test.i << ", " << test.read() << ", ";
        
        test.write(42);
        std::cout << "mock v: " << mocks::v << "\n";
    }
}
