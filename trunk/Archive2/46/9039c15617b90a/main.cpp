class TestError
{
public:
    TestError( const std::string &description )
        : m_description( description )
    { }

    ~TestError()
    { }

    std::string m_description;
};

template <typename U, typename V>
static void test_assert( const char *description, U benchmark, V value )
{
    std::ostringstream full_description;

    full_description << description
        << ": " << typeid(U).name() << " benchmark=" << benchmark
        <<  " " << typeid(V).name() << " value="     << value;

    if( (V)benchmark != value )
        throw TestError( full_description.str() );
    else
        std::cout << "PASSED: " << full_description.str() << std::endl;
}

int main() {
    std::string name{ "foo" };
    test_assert( name+" operator int", int(1), int(1) );
}