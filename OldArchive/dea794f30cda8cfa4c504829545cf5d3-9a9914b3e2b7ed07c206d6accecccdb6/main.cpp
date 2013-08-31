#include <memory>

template<typename T>
struct AutoPtr
{
#ifdef COMPILE_FOR_CX11
    typedef std::unique_ptr<T> Type;
#else
    typedef std::auto_ptr<T> Type;
#endif
};

class MockClass { };

namespace testing
{
    template<typename T>
    struct NiceMock : T { };
}

class Client
{
public:
    Client();
    Client(const Client& rhs);

private:
    mutable AutoPtr<MockClass>::Type embeddedMock;
};

Client::Client()
: embeddedMock(new ::testing::NiceMock<MockClass>())
//             ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
// Getting errors here!
{
}


Client::Client(const Client& rhs)
: embeddedMock(rhs.embeddedMock)
{
}

int main()
{
}