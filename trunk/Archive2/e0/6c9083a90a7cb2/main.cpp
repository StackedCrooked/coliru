#include <atomic>
#include <boost/intrusive_ptr.hpp>

struct Value;

struct Type {
    std::function<void(Value*)> destructor;
};

struct Value {
    Type* type;
    long refcount;

    static void operator delete(void* voidValue, std::size_t) {
        auto value = static_cast<Value*>(voidValue);
        value->type->destructor(value);
        ::operator delete(voidValue);
    }
};

extern "C" void mill_retain(Value* value) {
    ++value->refcount;
}

extern "C" void mill_release(Value* value) {
    --value->refcount;
    if (value->refcount == 0) {
        delete value;
    }
}

void intrusive_ptr_add_ref(Value* value) {
    mill_retain(value);
}

void intrusive_ptr_release(Value* value) {
    mill_release(value);
}

#include <iostream>

int main() {
    Type type;
    type.destructor = [] (Value* self) { std::cout << "destroying " << self << "!\n"; };
    boost::intrusive_ptr<Value> a(new Value);
    a->type = &type;
}