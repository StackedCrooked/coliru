#include <set>
#include <memory>

class foo
{
public:
    foo(int number) {}
};

int main()
{
    std::set<std::shared_ptr<foo>> objs;
    
    auto o = std::make_shared<foo>(100);
    
    objs.insert(o);
    
    objs.erase(o);
}