#include <utility>
#include <cassert>

template<typename Value>
struct expect_type {
    Value value;

    struct be_type {
        Value& ref;
        
        template<typename Other>
        bool equal(Other const& other)
        { return ref == other; }
    };
    
    struct to_type {
        Value& ref;
        
        be_type be { ref };
    };
    
    to_type to { value };
};

template<typename Value>
expect_type<Value> expect(Value&& value)
{ return { std::forward<Value>(value) }; }

int main()
{
    assert( expect(4).to.be.equal(5) );
}