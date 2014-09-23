#include <iostream>
#include <memory>

class ExpensiveResource final {
public:
    ExpensiveResource(const std::string& desc) : desc(desc) {
        std::clog << "\tConstructing ExpensiveResource \"" << desc << "\"\n";
    }
    ~ExpensiveResource() noexcept {
        std::clog << "\tDestroying ExpensiveResource \"" << desc << "\"\n";
    }
    const std::string& description() const {
        return desc;
    }
private:
    const std::string desc;
};

class Foo {
public:
    Foo(const std::string& id) : id(id) {
        std::clog << "Constructing Foo \"" << id << "\"\n";
        resource = std::make_unique<ExpensiveResource>(id + "::resource");
    }
    Foo(const Foo& rhs) = delete; // no copying
    Foo(Foo&& rhs) : id(rhs.id + " (moved)") {
        std::clog << "Move-constructing Foo from \"" << rhs.id << "\"\n";
        resource = std::move(rhs.resource);
        rhs.resource = nullptr;
    }
    virtual ~Foo() noexcept {
        std::clog << "Destroying Foo \"" << id << "\"\n";
    }
    const std::string& getId() const { return id; }
private:
    std::string id;
    std::unique_ptr<ExpensiveResource> resource;
};

Foo makeFoo(const char c) {
    if (c == 't') {
        Foo f{"temp-foo"};
        return f;
    } else {
        return {"never-foo"};
    }   
}

void playWithFoo(Foo&& foo) {
    std::clog << "Playing with '" << foo.getId() << "'\n";
}

int main()
{
    Foo foo1("foo1");
    playWithFoo(makeFoo('a'));
    Foo foo2 = makeFoo('t');
}
