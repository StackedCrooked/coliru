
template<class T, class Enable = typename std::enable_if<std::numeric_limits<T>::is_integer,
    T>::type>
	int foo(){}

template<class T>
 typename std::enable_if<std::numeric_limits<T>::is_integer,
	int >::type foo(){}