#include <boost/shared_ptr.hpp>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/composite_key.hpp>
#include <boost/multi_index/mem_fun.hpp>
#include <boost/type_traits/is_base_and_derived.hpp>
#include <boost/utility/enable_if.hpp>

using namespace boost::multi_index;

struct IFoo : private boost::noncopyable {
    virtual ~IFoo() {}
    virtual int getKey1() const = 0;
    virtual int getKey2() const = 0;
};

class Foo1 : IFoo {
    
    virtual ~Foo1() {}
    
    virtual int getKey1() const {
        return 1;
    }
    virtual int getKey2() const {
        return 1;
    }
};

class Foo2 : IFoo {
    
    virtual ~Foo2() {}
    
    virtual int getKey1() const {
        return 2;
    }
    virtual int getKey2() const {
        return 2;
    }
};

template <typename T>
struct FooContainer<T, typename boost::enable_if<boost::is_base_and_derived<IFoo, T>::value >::type > {
    typedef multi_index_container<
			T,
			indexed_by<
			hashed_unique<
			composite_key<
			T*,
			const_mem_fun<T,int,&T::getKey1>,
			const_mem_fun<T,int,&T::getKey2>
	>
	>
	>
	> Container_t;
};