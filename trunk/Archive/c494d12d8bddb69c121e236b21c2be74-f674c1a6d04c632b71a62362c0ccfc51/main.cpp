
#include <type_traits>
#include <memory>

typedef std::size_t ulword;

    template < typename TK, typename TV, typename TH = std::hash< TK >, 
		typename TKEq = std::equal_to< TK >, 
		typename TAlloc = std::allocator< std::pair<const TK, TV> > > 
	class Dictionary {
	public:
		typedef TK TKey;
		typedef TV TValue;
		typedef TH THash;
		typedef TKEq TKeyEquality;
		typedef TAlloc TAllocator;
		typedef std::pair<const TKey, TValue> TKeyValuePair;
		typedef std::pair<ulword, ulword> TMetaPair;
		typedef std::allocator_traits< TAllocator > TAllocatorTraits;
		typedef typename TAllocatorTraits::template rebind_alloc< TMetaPair > TMetaAllocator;
	};

int main () {
    Dictionary<int, int> arf;
}