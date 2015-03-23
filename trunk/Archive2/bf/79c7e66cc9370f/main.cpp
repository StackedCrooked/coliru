#include <cstddef>

extern void f();

class Value {
public:
    virtual ~Value() = 0;

private:
    std::size_t refcount;

    friend void mill_retain(void*);
    friend void mill_release(void*);
};
Value::~Value() = default;

class X : public Value {
public:
    ~X() { f(); }
};

int main() {
    Value* x = new X;
    delete x;
    return 0;
}