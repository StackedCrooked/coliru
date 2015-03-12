#include <iostream>
#include <tuple>
#include <string>

template <unsigned... Indices>
struct index_tuple {
    template <unsigned N>
    using append = index_tuple<Indices..., N>;
};

template <unsigned Size>
struct make_index_tuple {
    typedef typename make_index_tuple<Size-1>::type::template append<Size-1> type;
};

template <>
struct make_index_tuple<0u> {
    typedef index_tuple<> type;
};

template <unsigned Size>
struct make_shifted_index_tuple {
	typedef typename make_shifted_index_tuple<Size-1>::type::template append<Size-1> type;
};

template <>
struct make_shifted_index_tuple<1u> {
	typedef index_tuple<> type;
};

template <typename... Values>
struct Stack {    
	std::tuple<Values...> stack;
	
	Stack(const Values&... vals) : 
		stack(vals...)
	{}
	
	template <typename First, typename... Rest>
	struct stack_shift {
		typedef Stack<Rest...> type;
		
		template <typename... V>
		static Stack<V...> make_stack_(const V&... vals) {
			return Stack<V...>(vals...);
		}
		
		template <typename Tuple, unsigned... Indices>
		static type apply(const Tuple& tup, index_tuple<Indices...>) {
			return make_stack_(std::get<Indices>(tup)...);
		}
		
	public:
		static type make(const Stack<Values...>& prev) {
			typedef typename make_shifted_index_tuple<sizeof...(Values)>::type idx_tup;
			return apply(prev.stack, idx_tup());
		}
	};
	
	template <typename Add> 
	struct stack_push {
		typedef Stack<Add, Values...> type;
		
		template <typename... V>
		static Stack<V...> make_stack_(const V&... vals) {
			return Stack<V...>(vals...);
		}
	
		template <typename Tuple, unsigned... Indices>
		static type apply(const Add& v, const Tuple& tup, index_tuple<Indices...>) {
			return make_stack_(v, std::get<Indices>(tup)...);
		}
		
	public:
		static type make(const Add& v, const Stack<Values...>& prev) {
			typedef typename make_index_tuple<sizeof...(Values)>::type idx_tup;
			return apply(v, prev.stack, idx_tup());
		}
	};
    
    template <typename V> using push_type = typename stack_push<V>::type;
    typedef typename stack_shift<Values...>::type pop_type;
    typedef typename std::tuple_element<0, decltype(stack)>::type top_type;
	
	top_type top() const {
		return std::get<0>(stack);
	}
	
	pop_type pop() const {
		return stack_shift<Values...>::make(*this);
	}
	
	template <typename V>
	push_type<V> push(const V& v) const {
		return stack_push<V>::make(v, *this);
	}
	
	bool empty() const {
		return false;
	}
};

template <>
struct Stack<> {
public:
    template <typename V> using push_type = Stack<V>;

	Stack() {}
	
	bool empty() {
		return true;
	}
	
	template <typename V>
	Stack<V> push(const V& v) {
		return Stack<V>(v);
	}
	
private:
	void top();
	void pop();
};	

template <typename... V>
Stack<V...> make_stack(const V&... v) {
	return Stack<V...>(v...);
}

struct done {};

template <
    template <typename T> class Sp,
    typename T
>
void chain(const T& v) {
	try {
        chain<Sp>(Sp<T>()(v));
	}
    catch(done& d) {}
}



template <typename T>
struct print_stack;

template <>
struct print_stack<Stack<>> {
    Stack<> operator()(const Stack<>&) {
        throw done();    
    }
};

template <typename... V>
struct print_stack<Stack<V...>> {
    typename Stack<V...>::pop_type operator()(const Stack<V...>& s) {
        std::cout << s.top() << std::endl;
        return s.pop();
    }
};


int main() {
	auto stack = make_stack(1, 2, 3, 4, std::string("a string!"), true);
	chain<print_stack>(stack);
	
	return 0;
}