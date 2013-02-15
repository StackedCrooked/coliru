#include <memory>
#include <iostream>

    template< typename T, typename TDx>
	class ptrptr_type {
		typedef std::unique_ptr<T, TDx> parent_type;
		typedef typename parent_type::pointer pointer;

		parent_type* p;
		pointer a;
		ptrptr_type(const ptrptr_type& nocopy) {};
		ptrptr_type& operator=(const ptrptr_type& nocopy) {};

	public:
		ptrptr_type (std::unique_ptr<T, TDx>& ptr) : p(&ptr), a(ptr.release()) {}
		ptrptr_type(ptrptr_type&& mover) {p = mover.p; a = mover.a; mover.p = nullptr;}
		ptrptr_type& operator=(ptrptr_type&& mover) {p = mover.p; a = mover.a; mover.p = nullptr; return *this;}
		operator pointer*() { return &a ;}           
		~ptrptr_type () {if ( p ) p->reset( a ); }
	};

	template< typename T, typename TDx>
	ptrptr_type<T, TDx> ptrptr ( std::unique_ptr<T, TDx>& ptr ) { return ptrptr_type<T, TDx>( ptr ); }


	template < typename T, typename TDx = std::default_delete< T > >
	class ubiquitous_ptr : private std::unique_ptr<T, TDx> {
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
		ubiquitous_ptr (ubiquitous_ptr&& rhs) : parent_type( std::move(rhs) ) {}
		using parent_type::get;
		using parent_type::reset;
		using parent_type::release;
		using parent_type::swap;
		using parent_type::get_deleter;
		using parent_type::operator*;
		using parent_type::operator->;
		using parent_type::operator=;
		using parent_type::operator bool;
		ptrptr_type<T, TDx> get_ptrptr() {return ptrptr( *this );}
        
        ptrptr_type<T, TDx> operator& () {
            return get_ptrptr();
        }

        operator pointer () {
            return get();
        }

	};
    

void FuckingCOMShit ( int** initializecomgogo ) {
    delete *initializecomgogo; *initializecomgogo = new int( 48 );
}

int main ( int argc, char* argv[] ) {
    ubiquitous_ptr<int> commy(new int(24));
    int* ptr = commy;
    
    std::cout << *ptr << '\n';
    std::cout << *commy << '\n';
    
    FuckingCOMShit( &commy );
    
    std::cout << *commy << '\n';
}