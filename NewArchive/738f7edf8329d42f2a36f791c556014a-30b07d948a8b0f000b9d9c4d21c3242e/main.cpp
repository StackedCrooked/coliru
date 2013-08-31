#include <iostream>
#include <functional>

// Properties
template<typename datatype, typename name>
struct PropertyStorage
{
    static std::function<datatype&()> Get;
	static std::function<void(datatype)> Set;
};
template<typename datatype, typename name> std::function<datatype&()> PropertyStorage<datatype, name>::Get;
template<typename datatype, typename name> std::function<void(datatype)> PropertyStorage<datatype, name>::Set;

#define LengthOfMacroArgument(variable) sizeof(#variable)

#define PP_ARG_N(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, N, ...) N
#define PP_RSEQ_N() 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0
#define PP_COMMASEQ_N() 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0
#define PP_COMMA() ,
#define PP_HASCOMMA(...) PP_NARG_(__VA_ARGS__, PP_COMMASEQ_N())
#define PP_NARG_HELPER1(a, b, N) PP_NARG_HELPER2(a, b, N)
#define PP_NARG_HELPER2(a, b, N) PP_NARG_HELPER3_ ## a ## b(N)
#define PP_NARG_HELPER3_01(N) 0
#define PP_NARG_HELPER3_00(N) 1
#define PP_NARG_HELPER3_11(N) N
#define PP_NARG_(...) PP_ARG_N(__VA_ARGS__) 
#define NumberOfArguments(...) PP_NARG_HELPER1(PP_HASCOMMA(__VA_ARGS__), PP_HASCOMMA(PP_COMMA __VA_ARGS__ ()), PP_NARG_(__VA_ARGS__, PP_RSEQ_N()))

#define Attributes0()
#define Attributes1(a1) a1
#define Attributes2(a1, a2) a1 a2
#define Attributes3(a1, a2, a3) a1 a2 a3
#define Attributes4(a1, a2, a3, a4) a1 a2 a3 a4
#define Attributes5(a1, a2, a3, a4, a5) a1 a2 a3 a4 a5
#define CombineAttributesNumberOfArguments(x, y) x##y
#define EvaluateAttributes(number, ...) CombineAttributesNumberOfArguments(Attributes, number)(__VA_ARGS__)
#define Attributes(...) EvaluateAttributes(NumberOfArguments(__VA_ARGS__), __VA_ARGS__)

#define Property(datatype, name, get, set, attributes...) \
template<bool GetDefined##name, bool SetDefined##name, typename Enable##name = void> \
struct Property##name \
{ \
	/*Attributes(attributes)*/ \
	inline operator datatype&() \
	{ \
		return Value; \
	} \
	inline auto operator=(const datatype& value) -> decltype(*this)& \
	{ \
		Value = value; \
		return *this; \
	} \
	Property##name(std::function<datatype&()> Get, std::function<void(datatype)> Set) \
	{ \
		PropertyStorage<datatype, Property##name>::Get = Get; \
		PropertyStorage<datatype, Property##name>::Set = Set; \
	} \
	inline datatype* operator->() \
	{ \
		return &Value; \
	} \
private: \
	datatype Value; \
}; \
template<bool GetDefined##name, bool SetDefined##name> \
struct Property##name<GetDefined##name, SetDefined##name, typename std::enable_if<GetDefined##name && SetDefined##name>::type> \
{ \
	Attributes(attributes) \
	inline operator datatype&() \
	{ \
		return PropertyStorage<datatype, Property##name>::Get(); \
	} \
	inline auto operator=(const datatype& value) -> decltype(*this)& \
	{ \
		PropertyStorage<datatype, Property##name>::Set(value); \
		return *this; \
	} \
	Property##name(std::function<datatype&()> Get, std::function<void(datatype)> Set) \
	{ \
		PropertyStorage<datatype, Property##name>::Get = Get; \
		PropertyStorage<datatype, Property##name>::Set = Set; \
	} \
	inline datatype* operator->() \
	{ \
		return &PropertyStorage<datatype, Property##name>::Get(); \
	} \
private: \
	char NO_DATA[]; /* Illegal in C++11 (8.3.4/1) */ \
}; \
inline datatype& Get##name() { get throw; } \
inline void Set##name(datatype value) { set } \
Property##name<LengthOfMacroArgument(get) != 1, LengthOfMacroArgument(set) != 1> name = Property##name<LengthOfMacroArgument(get) != 1, LengthOfMacroArgument(set) != 1>(std::bind(&std::remove_reference<decltype(*this)>::type::Get##name, this), \
                                                                                                                                                                         std::bind(&std::remove_reference<decltype(*this)>::type::Set##name, this, std::placeholders::_1));

#define get
#define set

#define ISerializable \
Property(bool, Changed, get, set)

class Foo
{
private:
	int b;
public:
	Property(int, B, get { return b; }, set { b = value; B.Changed = true; }, ISerializable)
};

int main()
{
	std::cout << "sizeof(Foo) is " << sizeof(Foo) << std::endl;
	Foo foo;
	foo.B.Changed = false;
	std::cout << "Changed: " << foo.B.Changed << std::endl;
	foo.B = 42;
	std::cout << "Changed: " << foo.B.Changed << std::endl;
	std::cout << foo.B << std::endl;
	return 0;	
}