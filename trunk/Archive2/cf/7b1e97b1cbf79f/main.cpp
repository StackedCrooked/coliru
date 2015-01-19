#include <iostream>
#include <memory>


class foo {
    public:
    virtual void print_text() {
		std::cout << "foo\n";
	}
};

class bar : public foo {
    public:
	void print_text() {
		std::cout << "bar\n";
    }
};

class baz : public bar {
    public:
    void print_text(int err) {
        std::cout << "baz\n";
    }
};

int main(){
    std::unique_ptr<foo> f = std::make_unique<foo>();
    std::unique_ptr<foo> b = std::make_unique<bar>();
    std::unique_ptr<foo> c = std::make_unique<baz>();
    f->print_text();
    b->print_text();
    c->print_text();
}