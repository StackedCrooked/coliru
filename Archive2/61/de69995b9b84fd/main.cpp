#include <cstddef>
#include <type_traits>

#include <iostream>
#include <array>

// THIS LOOK OKAY?

	template <typename X = typename std::enable_if<is_slicable_t::value>::type>
	slice_t operator[] ( int i ) {
		return const_slice_t( res, dims, strides, origins );
	}

	template <typename X = typename std::enable_if<is_slicable_t::value>::type>
	const_slice_t operator[] ( int i ) const {
		return const_slice_t( res, dims, strides, origins );
	}

	reference operator[] ( index_type i ) {
		return res[ from_index( i, strides, origins ) ];
	}

	const_reference operator[] ( index_type i ) const {
		return res[ from_index( i, strides, origins ) ];
	}


int main () {
   
}