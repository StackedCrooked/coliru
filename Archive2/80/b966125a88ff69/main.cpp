#include <boost/variant.hpp>
#include <iostream>

namespace sg {
    namespace fields {
        struct sb {
            enum field_key_t { A, B };
            static uint32_t keyToRegBlockLen(const field_key_t& k) { return (int)k; }
            
        private:
            sb();
        };
        
        struct ts {
            enum field_key_t { C, D };
            static uint32_t keyToRegBlockLen(const field_key_t& k) { return (int)k; }
            
        private:
            ts();
        };
    }
}

typedef boost::variant<
    ::sg::fields::sb::field_key_t,
	::sg::fields::ts::field_key_t
> variant_field_key_t;


struct KeyToRegBlockLenVisitor : boost::static_visitor<uint32_t>
{
	uint32_t operator()(const ::sg::fields::sb::field_key_t& key) const
    //                  ^^^^^
	{
		return ::sg::fields::sb::keyToRegBlockLen(key);
	}
    
	uint32_t operator()(const ::sg::fields::ts::field_key_t& key) const
    //                  ^^^^^
	{
		return ::sg::fields::ts::keyToRegBlockLen(key);
	}
};

inline uint32_t keyToRegBlockLen(const variant_field_key_t& v)
{
	return boost::apply_visitor(KeyToRegBlockLenVisitor(), v);
}

int main()
{
    variant_field_key_t v1 = ::sg::fields::sb::A;
    variant_field_key_t v2 = ::sg::fields::ts::D;
    
    std::cout << keyToRegBlockLen(v1) << ' ' << keyToRegBlockLen(v2) << '\n';
}
