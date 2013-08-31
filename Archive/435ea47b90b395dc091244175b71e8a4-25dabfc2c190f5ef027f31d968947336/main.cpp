   
    template<typename T>
    T& declval();

    template<typename T, typename Arg>
	struct HasMember {                      
		typedef char yes[1];           
		typedef char no [2];           
		template <int> struct sfinae;
		static yes &chk(sfinae<sizeof(declval<T>().member(declval<Arg>()))>*);
		static no  &chk(...);
		static bool const value = sizeof(chk(0)) == sizeof(yes);
	};
