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

#define NumberOfArguments(...) \
    NumberOfArguments_(__VA_ARGS__, NumberOfArguments_RSEQ_N())
#define NumberOfArguments_(...) \
    NumberOfArguments_N(__VA_ARGS__)
#define NumberOfArguments_N( \
     _1, _2, _3, _4, _5, _6, _7, _8, _9,_10, \
    _11,_12,_13,_14,_15,_16,_17,_18,_19,_20, \
    _21,_22,_23,_24,_25,_26,_27,_28,_29,_30, \
    _31,_32,_33,_34,_35,_36,_37,_38,_39,_40, \
    _41,_42,_43,_44,_45,_46,_47,_48,_49,_50, \
    _51,_52,_53,_54,_55,_56,_57,_58,_59,_60, \
    _61,_62,_63,  N, ...) N
#define NumberOfArguments_RSEQ_N() \
    63,62,61,60, \
    59,58,57,56,55,54,53,52,51,50, \
    49,48,47,46,45,44,43,42,41,40, \
    39,38,37,36,35,34,33,32,31,30, \
    29,28,27,26,25,24,23,22,21,20, \
    19,18,17,16,15,14,13,12,11,10, \
     9, 8, 7, 6, 5, 4, 3, 2, 1, 0

#define Attributes0()
#define Attributes1(a1) a1
#define Attributes2(a1, a2) a1 a2
#define Attributes3(a1, a2, a3) a1 a2 a3
#define Attributes4(a1, a2, a3, a4) a1 a2 a3 a4
#define Attributes5(a1, a2, a3, a4, a5) a1 a2 a3 a4 a5
#define Attributes6(a1, a2, a3, a4, a5, a6) a1 a2 a3 a4 a5 a6
#define Attributes7(a1, a2, a3, a4, a5, a6, a7) a1 a2 a3 a4 a5 a6 a7
#define Attributes8(a1, a2, a3, a4, a5, a6, a7, a8) a1 a2 a3 a4 a5 a6 a7 a8
#define Attributes9(a1, a2, a3, a4, a5, a6, a7, a8, a9) a1 a2 a3 a4 a5 a6 a7 a8 a9
#define Attributes10(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10) a1 a2 a3 a4 a5 a6 a7 a8 a9 a10
#define Attributes11(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11) a1 a2 a3 a4 a5 a6 a7 a8 a9 a10 a11
#define Attributes12(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12) a1 a2 a3 a4 a5 a6 a7 a8 a9 a10 a11 a12
#define Attributes13(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13) a1 a2 a3 a4 a5 a6 a7 a8 a9 a10 a11 a12 a13
#define Attributes14(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14) a1 a2 a3 a4 a5 a6 a7 a8 a9 a10 a11 a12 a13 a14
#define Attributes15(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15) a1 a2 a3 a4 a5 a6 a7 a8 a9 a10 a11 a12 a13 a14 a15
#define CombineAttributesNumberOfArguments(x, y) x##y
#define EvaluateAttributes(number, ...) CombineAttributesNumberOfArguments(Attributes, number)(__VA_ARGS__)
#define Attributes(...) EvaluateAttributes(NumberOfArguments(__VA_ARGS__), __VA_ARGS__)

#define Property(datatype, name, get, set, attributes...) \
template<bool GetDefined##name, bool SetDefined##name, typename Enable##name = void> \
struct Property##name \
{ \
	Attributes(attributes) \
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
struct Property##name<GetDefined##name, SetDefined##name, typename std::enable_if<!GetDefined##name && SetDefined##name>::type> \
{ \
	Attributes(attributes) \
	inline operator datatype&() \
	{ \
		static_assert(true, "Property has no get defined."); \
		throw; \
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
private: \
	char NO_DATA[]; /* Illegal in C++11 (8.3.4/1) */ \
}; \
template<bool GetDefined##name, bool SetDefined##name> \
struct Property##name<GetDefined##name, SetDefined##name, typename std::enable_if<GetDefined##name && !SetDefined##name>::type> \
{ \
	Attributes(attributes) \
	inline operator datatype&() \
	{ \
		return PropertyStorage<datatype, Property##name>::Get(); \
	} \
	inline auto operator=(const datatype& value) -> decltype(*this)& \
	{ \
		static_assert(true, "Property has no set defined."); \
		return *this; \
	} \
	Property##name(std::function<datatype&()> Get, std::function<void(datatype)> Set) \
	{ \
		PropertyStorage<datatype, Property##name>::Get = Get; \
		PropertyStorage<datatype, Property##name>::Set = Set; \
	} \
private: \
	char NO_DATA[]; /* Illegal in C++11 (8.3.4/1) */ \
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
	Property(int, A, get, set)
	Property(int, B, get { return b; }, set { b = value; B.Changed = true; }, ISerializable)
	Property(int, B2, get { return b; }, set)
	Property(int, B3, get, set { b = value; })
};

class Bar
{
private:
	Foo b;
public:
	Property(Foo, A, get, set)
	Property(Foo, B, get { return b; }, set { b = value; })
};

int main()
{
	std::cout << "sizeof(Foo) is " << sizeof(Foo) << std::endl;
	Foo foo;
	foo.A = 42;
	std::cout << foo.A << std::endl;
	std::cout << "Changed: " << foo.B.Changed << std::endl;
	foo.B = 42;
	std::cout << "Changed: " << foo.B.Changed << std::endl;
	std::cout << foo.B << std::endl;
	foo.B3 = 43;
	std::cout << foo.B2 << std::endl;
	
	std::cout << "sizeof(Bar) is " << sizeof(Bar) << std::endl;
	Bar bar;
	bar.A->A = 44;
	std::cout << bar.A->A << std::endl;
	bar.B->A = 44;
	std::cout << bar.B->A << std::endl;
	return 0;	
}