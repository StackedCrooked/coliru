template <typename TIterator>
TIterator EncodeOne( codepoint codepoint, TIterator iterator  ) const {
	typedef typename expanded_iterator_traits<TIterator>::value_type value_type;
	return EncodeOne( codepoint, iterator, is_integer_equal<sizeof( value_type ), 1>::type() );
}

template <typename TIterator>
TIterator EncodeOne( codepoint codepoint, TIterator iterator, std::false_type is1 ) const {
	//"Override" 2
}

template <typename TIterator>
TIterator EncodeOne( codepoint codepoint, TIterator iterator, std::true_type is1 ) const {
	// "Override" 1
}


int main () {
 
}