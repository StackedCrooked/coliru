#include <boost/shared_ptr.hpp>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/composite_key.hpp>
#include <boost/multi_index/mem_fun.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_base_and_derived.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/utility/enable_if.hpp>

#include <iostream>

using namespace boost::multi_index;

struct IFoo;
typedef boost::shared_ptr<IFoo> IFooPtr_t;

struct IFoo : private boost::noncopyable {
    virtual ~IFoo() {}
    virtual int getKey1() const = 0;
    virtual int getKey2() const = 0;
};

struct Foo1 : IFoo {
    
    Foo1() {}
    
    virtual ~Foo1() {}
    
    virtual int getKey1() const {
        return 1;
    }
    virtual int getKey2() const {
        return 1;
    }
};

struct Foo2 : IFoo {
    
    Foo2() {}
    
    virtual ~Foo2() {}
    
    virtual int getKey1() const {
        return 2;
    }
    virtual int getKey2() const {
        return 2;
    }
};

template<class T, class Enable = void>
class FooContainer;

//template <typename T, typename boost::enable_if<boost::is_base_of<IFoo, T>::value>::type>
template <class T>
struct FooContainer<T,typename boost::enable_if<boost::is_base_of<IFoo, T> >::type> {
    typedef multi_index_container<
			T,
			indexed_by<
			hashed_unique<
			composite_key<
			T,
			const_mem_fun<T,int,&T::getKey1>,
			const_mem_fun<T,int,&T::getKey2>
	>
	>
	>
	> raw_type;
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
	> raw_ptr_type;
    typedef multi_index_container<
        	boost::shared_ptr<T>,
			indexed_by<
			hashed_unique<
			composite_key<
			T,
			const_mem_fun<T,int,&T::getKey1>,
			const_mem_fun<T,int,&T::getKey2>
	>
	>
	>
	> shared_ptr_type;
};

typedef multi_index_container<
    	IFooPtr_t,
		indexed_by<
		hashed_non_unique<
		composite_key<
		IFoo,
    		const_mem_fun<IFoo,int,&IFoo::getKey1>,
			const_mem_fun<IFoo,int,&IFoo::getKey2>
>
>
>
> FooIndexedContainer_t;

int main(int argc, char** argv){

    /* Extern from struct */
    FooIndexedContainer_t foo_container_ext;
    foo_container_ext.insert(IFooPtr_t(new Foo1()));

    FooIndexedContainer_t::iterator it_ext = foo_container_ext.find(boost::make_tuple(1,1));
    
    if(it_ext != foo_container_ext.end())
        std::cout << "Found: keys: "<<(*it_ext)->getKey1() << " " <<  (*it_ext)->getKey2() <<std::endl;
    else
        std::cout << "Too bad " << std::endl;
        
    /* Struct::raw_type */
    /*FooContainer<Foo1>::raw_type foo_container_raw;
    Foo1 foo_1();
    foo_container_raw.insert(foo_1);
    
    FooContainer<Foo1>::raw_type::iterator it_raw = foo_container_raw.find(boost::make_tuple(1,1));
    
    if(it_raw != foo_container_raw.end())
        std::cout << "Found raw: keys: "<<(*it_raw).getKey1() << " " <<  (*it_raw).getKey2() <<std::endl;
    else
        std::cout << "Too bad " << std::endl;*/
        
    /* Struct::raw_ptr_type */
    FooContainer<Foo1>::raw_ptr_type foo_container_raw_ptr;
    foo_container_raw_ptr.insert(new Foo1());
    
    FooContainer<Foo1>::raw_ptr_type::iterator it_raw_ptr = foo_container_raw_ptr.find(boost::make_tuple(1,1));
    
    if(it_raw_ptr != foo_container_raw_ptr.end())
        std::cout << "Found raw: keys: "<<(*it_raw_ptr)->getKey1() << " " <<  (*it_raw_ptr)->getKey2() <<std::endl;
    else
        std::cout << "Too bad " << std::endl;
    
    return 0;
}
