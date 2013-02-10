#include <iostream>
#include <memory>
#include <utility>

template <typename T>
struct remove_type;

template <typename T>
struct remove_type<T*> {
	typedef void* type;
};

template <typename T>
struct remove_type<T**> {
	typedef void** type;
};

template <typename T>
struct remove_type<T***> {
	typedef void*** type;
};

template< typename T, typename TDx>
class ptrptr_type {
public:
	typedef std::unique_ptr<T, TDx> parent_type;
	typedef typename parent_type::pointer pointer;
	typedef typename remove_type<pointer>::type erasure_pointer;

private:
	parent_type* p;
	pointer a;
	ptrptr_type(const ptrptr_type& nocopy) { };
	ptrptr_type& operator=(const ptrptr_type& nocopy) { return *this; };

public:
	ptrptr_type (std::unique_ptr<T, TDx>& ptr) : p(&ptr), a(ptr.release()) {}
	ptrptr_type(ptrptr_type&& mover) {p = mover.p; a = mover.a; mover.p = nullptr;}
	ptrptr_type& operator=(ptrptr_type&& mover) {p = mover.p; a = mover.a; mover.p = nullptr; return *this;}
	operator pointer*() { return &a; }
	operator pointer&() { return a; }
	explicit operator erasure_pointer () { return reinterpret_cast<erasure_pointer>( a ); }
	explicit operator erasure_pointer* () { return reinterpret_cast<erasure_pointer*>( &a ); }
	~ptrptr_type () {if ( p ) p->reset( a ); }
};

template< typename T, typename TDx>
ptrptr_type<T,TDx> ptrptr ( std::unique_ptr<T, TDx>& ptr ) { return ptrptr_type<T, TDx>( ptr ); }


template < typename T, typename TDx = std::default_delete< T > >
class ubiquitous_ptr : private std::unique_ptr<T, TDx> {
private:
	ubiquitous_ptr& operator=(const ubiquitous_ptr& nocopy) { return *this; };

public:
	typedef std::unique_ptr<T, TDx> parent_type;
	typedef typename parent_type::pointer pointer;
	typedef typename parent_type::element_type element_type;
	typedef typename parent_type::deleter_type deleter_type;
	
public:
	ubiquitous_ptr () : parent_type() {}
	ubiquitous_ptr (pointer p) : parent_type(p) {}
	ubiquitous_ptr (pointer p, const deleter_type& d) : parent_type(p, d) {}
	ubiquitous_ptr (pointer p, deleter_type&& d) : parent_type(p, std::move(d)) {}
	ubiquitous_ptr (std::nullptr_t p) : parent_type(p) {}
	ubiquitous_ptr (ubiquitous_ptr&& rhs) : parent_type( std::move(rhs) ) { }
	using parent_type::get;
	using parent_type::reset;
	using parent_type::release;
	using parent_type::swap;
	using parent_type::get_deleter;
	using parent_type::operator*;
	using parent_type::operator->;
#ifndef _MSC_VER
	using parent_type::operator bool;
	using parent_type::operator=;
#else
	operator bool ( ) const { return get() != nullptr; }
	ubiquitous_ptr& operator= ( ubiquitous_ptr&& right ) { reset(right.release()); return *this; }
	ubiquitous_ptr& operator= ( pointer right ) { reset( right ); return *this; }
	bool operator== ( const ubiquitous_ptr& right ) const { return get() == right.get(); }
	bool operator== ( pointer right ) const { return get() == right; }
	bool operator== ( std::nullptr_t right ) const { return get() == right; }
	bool operator!= ( const ubiquitous_ptr& right ) const { return get() != right.get(); }
	bool operator!= ( pointer right ) const { return get() != right; }
	bool operator!= ( std::nullptr_t right ) const { return get() != right; }
#endif /* _MSC_VER */
	operator pointer () { return get(); };
	ptrptr_type<T, TDx> operator& () { return get_ptrptr(); }
	ptrptr_type<T, TDx> get_ptrptr() { return ptrptr( (std::unique_ptr<T, TDx>&)(*this) ); }

};

template<typename T, typename TDx>
static bool operator== ( typename ubiquitous_ptr<T, TDx>::pointer right, const ubiquitous_ptr<T, TDx>& left ) { return left.get() == right; }
template<typename T, typename TDx>
static bool operator== ( std::nullptr_t right, const ubiquitous_ptr<T, TDx>& left ) { return left.get() == right; }
template<typename T, typename TDx>
static bool operator!= ( typename ubiquitous_ptr<T, TDx>::pointer right, const ubiquitous_ptr<T, TDx>& left ) { return left.get() != right; }
template<typename T, typename TDx>
static bool operator!= ( std::nullptr_t right, const ubiquitous_ptr<T, TDx>& left ) { return left.get() != right; }


template< typename T, typename TDx>
ptrptr_type<T,TDx> ptrptr ( ubiquitous_ptr<T, TDx>& ptr ) { return ptr.get_ptrptr(); }


void MicrosoftCOM ( void** mem ) {
    
    *mem = (void*)(new int(48));
    
}

    
int main ( int argc, char* argv[] ) {
    
    ubiquitous_ptr<int> yay ( new int(24) );
    
    std::cout << *yay << std::endl;
    MicrosoftCOM( (void**)&yay );
    std::cout << *yay << std::endl;
    
    return 0;
}