#include <memory>
struct IMoo { virtual ~IMoo() = default; };
struct MooA : public IMoo {};
struct MooB : public IMoo {};

class Foo
{
public:
    Foo() : m_moo(false ? static_cast<std::shared_ptr<IMoo>>(std::make_shared<MooA>()) : std::make_shared<MooB>())
    {
    }

private:
    std::shared_ptr<IMoo> m_moo;
};

 
int main() {

}
