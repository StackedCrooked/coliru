#include <unordered_map>
#include <set>
#include <vector>
#include <array>
#include <bitset>
#include <utility>
#include <iostream>

template <typename TSeqItem, typename TValue>
class Trie {
private:
    typedef std::pair<std::set<TSeqItem>, TValue> TNode;
	typedef std::unordered_map<std::size_t, TNode> TDepthNode;
	std::unordered_map<TSeqItem, TDepthNode> tree;

public:

	Trie () {

	}

	template <typename TContainer>
	void Insert ( TContainer& container, const TValue& value ) {
		return Insert( std::begin( container ), std::end( container ), value );
	}

	template <typename TIterator>
	void Insert ( TIterator seqbegin, TIterator seqend, const TValue& value ) {
		std::size_t depth = 0;
		if ( seqbegin == seqend )
			return;
		TIterator current = seqbegin;
		TNode* node = nullptr;
		TSeqItem* k = nullptr;
		while ( current != seqend ) {
			k = std::addressof( *current );
			
			TDepthNode& depthnode = tree[ *k ];
			node = std::addressof( depthnode[ depth ] );
			
			++depth;
			++current;
		}
		if ( node != nullptr ) {
			node->first.insert( *k );
			node->second = value;
		}
	}

	template <typename TContainer>
	bool TryGetValue ( TContainer& container, TValue& value ) {
		return TryGetValue( std::begin( container ), std::end( container ), value );
	}

	template <typename TIterator>
	bool TryGetValue ( TIterator seqbegin, TIterator seqend, TValue& value ) {
		std::size_t depth = 0;
		if ( seqbegin == seqend )
			return false;
		TIterator current = seqbegin;
		TNode* node = nullptr;
		TSeqItem* k = nullptr;
		while ( current != seqend ) {
			k = std::addressof( *current );

			auto existingk = tree.find( *k );
			if ( existingk == tree.end() )
				return false;

			TDepthNode& depthnode = existingk->second;
			auto hasdepth = depthnode.find( depth );
			if ( hasdepth == depthnode.end() )
				return false;
		
			node = std::addressof( hasdepth->second );

			++current;
			++depth;
		}
		if ( node == nullptr || 
			node->first.find( *k ) == node->first.end() )
			return false;

		value = node->second;
		
		return true;
	}

};

int main ( int argc, char** argv ) {
	std::array<int, 3> arr = { 1, 2, 3 };
	std::array<int, 3> arr2 = { 1, 2, 2 };
	int val = 0xC1CADA;

	Trie<int, int> lookup;
	std::cout << std::hex;
	val = 0xC1CADA;
	std::cout << lookup.TryGetValue( arr, val ) << std::endl;
	std::cout << val << std::endl;
	val = 0xC1CADA;
	std::cout << lookup.TryGetValue( arr2, val ) << std::endl;
	std::cout << val << std::endl << std::endl;
	
	lookup.Insert( arr, 0xFF );
	val = 0xC1CADA;
	std::cout << lookup.TryGetValue( arr, val ) << std::endl;
	std::cout << val << std::endl;
	val = 0xC1CADA;
	std::cout << lookup.TryGetValue( arr2, val ) << std::endl;
	std::cout << val << std::endl << std::endl;
	
	lookup.Insert( arr2, 0xF0 );
	val = 0xC1CADA;
	std::cout << lookup.TryGetValue( arr, val ) << std::endl;
	std::cout << val << std::endl;
	val = 0xC1CADA;
	std::cout << lookup.TryGetValue( arr2, val ) << std::endl;
	std::cout << val << std::endl << std::endl;

	lookup.Insert( arr2, 0xFE );
	val = 0xC1CADA;
	std::cout << lookup.TryGetValue( arr, val ) << std::endl;
	std::cout << val << std::endl;
	val = 0xC1CADA;
	std::cout << lookup.TryGetValue( arr2, val ) << std::endl;
	std::cout << val << std::endl << std::endl;
}