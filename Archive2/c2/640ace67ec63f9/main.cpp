#include <utility>
#include <cassert>

template<typename Value>
struct be_type {
    Value& ref;
    
    template<typename Other>
    bool equal(Other const& other)
    { return ref == other; }
};

template<typename Value>
struct to_type {
    Value& ref;
    
    be_type<Value> be { ref };
};

template<typename Value>
struct expect_type {
    Value value;
    
    to_type<Value> to { value };
};

template<typename Value>
expect_type<Value> expect(Value&& value)
{ return { std::forward<Value>(value) }; }

int main()
{
    assert( expect(4).to.be.equal(5) );
}