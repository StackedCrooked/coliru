#include <memory>
#include <type_traits>

template <typename TDx>
struct optional_delete {
	bool usedeleter;
	TDx deleter;

	optional_delete ( bool calldelete = true, TDx&& deleter = TDx() );

	template<typename T>
	void operator() ( T* ptr ) const;
};

template <typename TDx>
optional_delete<TDx>::optional_delete( bool calldelete /*= true */, TDx&& deleter /*= TDx()*/ ) 
: usedeleter( calldelete ), deleter(std::move(deleter)) {

}

// Uh. What do?
template <typename TDx>
template <typename T>
void optional_delete<TDx>::operator()( T* ptr ) const {
	if ( usedeleter )
		deleter( ptr );
}

int main() {
    std::unique_ptr<int, optional_delete<std::default_delete<int>>> ptr;
    
}