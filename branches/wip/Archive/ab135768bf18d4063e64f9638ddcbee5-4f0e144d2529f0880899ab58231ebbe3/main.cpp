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
struct Foo1;
struct Foo2;
typedef boost::shared_ptr<IFoo> IFooPtr_t;
typedef boost::shared_ptr<Foo1> Foo1Ptr_t;
typedef boost::shared_ptr<Foo2> Foo2Ptr_t;

struct LogicalAnd {
    bool operator()(const int& argVal1, const int& argVal2) const {
        std::cout << "Testing: " << argVal1 << " and " << argVal2<<std::endl;
		return ((int)(argVal1 & argVal2) == argVal1);
	}
};

struct IFoo : private boost::noncopyable {
    virtual ~IFoo() {}
    virtual int getKey1() const = 0;
    virtual int getKey2() const = 0;
};

namespace CustomKey {
    typedef enum {
        VAL1 = 0x00000001,
        VAL2 = 0x00000002,
        ALL = 0xFFFFFFFF
    } type;
}

struct Foo1 : IFoo {
    
    Foo1() {}
    
    virtual ~Foo1() {}
    
    virtual int getKey1() const {
        return CustomKey::ALL;
    }
    virtual int getKey2() const {
        return CustomKey::VAL2;
    }
};

struct Foo2 : IFoo {
    
    Foo2() {}
    
    virtual ~Foo2() {}
    
    virtual int getKey1() const {
        return CustomKey::VAL1;
    }
    virtual int getKey2() const {
        return CustomKey::ALL;
    }
};

template<class T, class Enable = void>
class FooContainer;

//template <typename T, typename boost::enable_if<boost::is_base_of<IFoo, T>::value>::type>
template <class T>
struct FooContainer<T,typename boost::enable_if<boost::is_base_of<IFoo, T> >::type> {
    typedef multi_index_container<
            boost::shared_ptr<T>,
			indexed_by<
			hashed_non_unique<
			composite_key<
			T,
			const_mem_fun<T,int,&T::getKey1>,
			const_mem_fun<T,int,&T::getKey2>
	>,
    composite_key_hash<
          boost::hash<int>,
          boost::hash<int>
    >,
    composite_key_equal_to<
    LogicalAnd,
    LogicalAnd
    >
	>
	>
	> shared_ptr_type;
};



int main(int argc, char** argv){
    
    FooContainer<IFoo>::shared_ptr_type foo_container_shared_ptr;
    
    foo_container_shared_ptr.insert(IFooPtr_t(new Foo1()));
    foo_container_shared_ptr.insert(IFooPtr_t(new Foo2()));
    
    //std::cout<< "VAL1: " << CustomKey::VAL1 << ", VAL2: " << CustomKey::VAL2 << ", ALL: " << CustomKey::ALL << std::endl;
    
    FooContainer<IFoo>::shared_ptr_type::iterator it = foo_container_shared_ptr.find(boost::make_tuple(CustomKey::ALL,CustomKey::ALL));
    
    std::cout << "Result: "<< (int)(CustomKey::VAL2 & CustomKey::ALL) << std::endl;
    
    if((int)(CustomKey::VAL2 & CustomKey::ALL) == CustomKey::VAL2)
        std::cout << "ok" << std::endl;
    
    if(it != foo_container_shared_ptr.end())
        std::cout << "Found: keys: "<<(*it)->getKey1() << " " <<  (*it)->getKey2() <<std::endl;
    while( (it=foo_container_shared_ptr.find(boost::make_tuple(CustomKey::ALL,CustomKey::ALL))) != foo_container_shared_ptr.end() ) {
        std::cout << "Found: keys: "<<(*it)->getKey1() << " " <<  (*it)->getKey2() <<std::endl;
    }
    
    
    return 0;
}
