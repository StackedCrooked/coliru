#include <string>
#include <vector>
#include <memory>

namespace lib
{

class Foo_impl;

class Foo
{
    public:
        Foo();
        ~Foo();

    private:
        Foo(const Foo&);
        Foo& operator=(const Foo&);

        std::unique_ptr<Foo_impl> m_impl;

        friend class Foo_impl;
};

}

int main() {}