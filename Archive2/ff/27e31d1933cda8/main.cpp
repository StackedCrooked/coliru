#include <iterator>

namespace Furrovine {

    template <typename Impl, typename T, typename TDiff = std::ptrdiff_t, typename TPointer = T*, typename TReference = T&>
	struct forward_iterator : public std::iterator<std::forward_iterator_tag, T, TDiff, TPointer, TReference> {

        /*using value_type = T;
        using difference_type = TDiff;
        using pointer = TPointer
        using reference = TReference;
        using iterator_category = std::forward_iterator_tag;
*/
		Impl operator++ ( int ) {
			Impl& impl = *static_cast<Impl*>( this );
			Impl old( impl );
			impl.next( );
			return old;
		}

		Impl& operator++ ( ) {
			Impl& impl = *static_cast<Impl*>( this );
			impl.next( );
			return impl;
		}

		const reference operator* ( ) const {
			const Impl& impl = *static_cast<const Impl*>( this );
			return impl.dereference( );
		}

		reference operator* ( ) {
			Impl& impl = *static_cast<Impl*>( this );
			return impl.dereference( );
		}

		const reference operator-> ( ) const {
			const Impl& impl = *static_cast<const Impl*>( this );
			return impl.dereference( );
		}

		reference operator-> ( ) {
			Impl& impl = *static_cast<Impl*>( this );
			return impl.dereference( );
		}

		bool operator== ( const Impl& right ) const {
			const Impl& left = *static_cast<const Impl*>( this );
			return left.equals( right );
		}

		bool operator!= ( const Impl& right ) const {
			const Impl& left = *static_cast<const Impl*>( this );
			return !left.equals( right );
		}

	};

}


int main () {
    
    
    
}