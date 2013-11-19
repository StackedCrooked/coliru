#include <iostream>
#include <type_traits>
#include <memory>

    template <typename T>
    struct remove_type {
		typedef void type;
	};

	template <typename T>
	struct remove_type<T*> {
		typedef typename remove_type<T>::type* type;
	};

    template <typename TTo, typename Tp>
	static TTo static_cast_return( std::true_type, Tp&& ptr ) {
		return ptr;
	}

	template <typename TTo, typename Tp>
	static TTo static_cast_return( std::false_type, Tp&& ptr ) {
		return static_cast<TTo>( ptr );
	}

    template <typename TTo, typename T, typename Tp>
    static TTo static_cast_return( Tp&& ptr ) {
        typedef typename std::is_same<TTo, T>::type is_same_t;
		return static_cast_return<TTo>( is_same_t(), std::forward<T>( ptr ) );
	}
    
    template <typename TParent, typename TPtr = typename std::remove_pointer<typename TParent::pointer>::type, bool isvoid = std::is_void<TPtr>::value>
    class ptrptr_t;

	template <typename TParent, typename TPtr>
	class ptrptr_t<TParent, TPtr, false> {
	public:
		typedef TParent parent_type;
		typedef TPtr* pointer;
		typedef typename parent_type::pointer parent_pointer;
		typedef typename remove_type<pointer>::type erasure_pointer;

	private:
		parent_type* p;
		pointer a;
		ptrptr_t( const ptrptr_t& nocopy ) {};
		ptrptr_t& operator=( const ptrptr_t& nocopy ) { return *this; };

	public:
		ptrptr_t( parent_type& ptr ) : p( std::addressof( ptr ) ), a( static_cast_return<pointer, parent_pointer>( ptr.release( ) ) ) {}
		ptrptr_t( ptrptr_t&& mover ) { p = mover.p; a = mover.a; mover.p = nullptr; }
		ptrptr_t& operator=( ptrptr_t&& mover ) { p = mover.p; a = mover.a; mover.p = nullptr; return *this; }
		operator pointer*( ) { return std::addressof( a ); }
		operator pointer&( ) { return a; }
		explicit operator erasure_pointer ( ) { return reinterpret_cast<erasure_pointer>( a ); }
		explicit operator erasure_pointer* ( ) { return reinterpret_cast<erasure_pointer*>( std::addressof( a ) ); }
		~ptrptr_t( ) { if ( p ) p->reset( static_cast_return<parent_pointer, pointer>( a ) ); }
	};

	template <typename TParent, typename TPtr>
	class ptrptr_t<TParent, TPtr, true> {
	public:
		typedef TParent parent_type;
		typedef TPtr* pointer;
		typedef typename parent_type::pointer parent_pointer;

	private:
		parent_type* p;
		pointer a;
		ptrptr_t( const ptrptr_t& nocopy ) {};
		ptrptr_t& operator=( const ptrptr_t& nocopy ) { return *this; };

	public:
		ptrptr_t( parent_type& ptr ) : p( std::addressof( ptr ) ), a( static_cast_return<pointer, parent_pointer>( ptr.release( ) ) ) {}
		ptrptr_t( ptrptr_t&& mover ) { p = mover.p; a = mover.a; mover.p = nullptr; }
		ptrptr_t& operator=( ptrptr_t&& mover ) { p = mover.p; a = mover.a; mover.p = nullptr; return *this; }
		operator pointer*( ) { return std::addressof( a ); }
		operator pointer&( ) { return a; }
		~ptrptr_t( ) { if ( p ) p->reset( static_cast_return<parent_pointer, pointer>( a ) ); }
	};


    template <typename TPtr>
    ptrptr_t<TPtr> ptrptr( TPtr& p ) { return ptrptr_t<TPtr>( p ); }

	template <typename TCast, typename TPtr>
	ptrptr_t<TPtr, TCast> ptrptr( TPtr& p ) { return ptrptr_t<TPtr, TCast>( p ); }

void com_style_funcs ( int** pint, int count ) {
    for ( int i =0; i < count; ++i )
        pint[i] = new int(20);
}


int main () {
   // Type-erased void pointer
   std::unique_ptr<void> arf( new int(24) );
   std::cout << *static_cast<int*>( arf.get() ) << std::endl;
   com_style_funcs( ptrptr<int>( arf ), 1 );
   std::cout << *static_cast<int*>( arf.get() ) << std::endl;
   
}
