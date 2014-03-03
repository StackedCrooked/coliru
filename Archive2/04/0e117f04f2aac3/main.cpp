    

    #include <iostream>
     
    template<typename... Args> class X;
     
    template<typename T>
    class X<T> {
     public:
        T value;
        explicit X(T value_) : value(value_) {}
    };
     
    template<typename T, typename... Args>
    class X<T, Args...> : public X<Args...> {
     public:
        T value;
        explicit X(T value_, Args... args) : X<Args...>(args...), value(value_) {}
    };

    template<std::size_t> struct compile_time_size {};
    
    template<typename T, typename... Ts>
    std::ostream& output_helper(std::ostream&, const X<T, Ts...>&, compile_time_size<0>) = delete;

template<typename T, typename... Ts>
	std::ostream& output_helper(std::ostream& stream, const X<T, Ts...>& value, compile_time_size<1>)
	{
        stream << value.value;
        return stream;
	}
    template<typename T, typename... Ts, std::size_t N>
	std::ostream& output_helper(std::ostream& stream, const X<T, Ts...>& value, compile_time_size<N>)
	{
        stream << value.value << " " << static_cast< X<Ts...> const& >(value);
        return stream;
	}
    template<typename... Ts>
    std::ostream& operator<<(std::ostream& stream, const X<Ts...>& value) {
    	return output_helper( stream, value, compile_time_size<sizeof...(Ts)>() );
    }

    class Person : public X<std::string, int, int> {
     public:
       Person(std::string name, int age, int foo) : X<std::string, int, int>(name, age, foo) {}
    };
     
     
    int main()
    {
       Person p("Me", 35, 42);
       std::cout << p;// << std::endl;
       return 0;
    }

