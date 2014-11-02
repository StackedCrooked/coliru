#include <iostream>
#include <type_traits>
#include <vector>

template< int CHANNEL_COUNT > struct Channels {

    static constexpr int channels = CHANNEL_COUNT ;
};

template< typename T, int = 0 > struct is_channel_ : std::false_type {} ;
template< int N > struct is_channel_< Channels<N> > : std::true_type {} ;
template< typename T > constexpr bool is_channel() { return is_channel_<T>::value ; }

template< typename T > struct Cable {

    static_assert( is_channel<T>(), "Cable must be intantiated with type Channels<N>" ) ;

    static constexpr int channels = T::channels;
	std::vector<float> audio[channels];

	Cable() {
		for( int i = 0; i < channels; ++i ) {
			for( int s = 0; s < 5; s++ ) audio[i].push_back(i);
        }
	}
};

template<int channel_count>
struct Tricked {
    static constexpr int channels = channel_count;
};

int main() {
    Cable< Channels<3> > this_is_fine ;
    std::cout << "ok\n\n" ;
    
    #ifdef NOT_OK
        Cable< Tricked<3> > this_is_not_ok ;
    #endif // NOT_OK
}
