#include <iostream>

struct BitProxy
{
    char &ByteRef;
	char Mask;
	
	BitProxy& operator=(bool v)
	{
		if(v) {ByteRef |= Mask;}
		else {ByteRef &= ~Mask;}
		return *this;
	}
	
	operator bool() const {return ByteRef & Mask;}
};

template <unsigned NumBits, typename EnumType, typename UnderlyingType>
struct EnumSet
{
	// how much bytes we need
	static constexpr unsigned Size = (NumBits - 1) / 8 + 1;
	char Bytes[Size];
	
	BitProxy operator[](EnumType v)
	{
		unsigned byte_ix = unsigned(UnderlyingType(v)) / 8;
		unsigned bit_ix = unsigned(UnderlyingType(v)) & 7;
		return BitProxy {Bytes[byte_ix], char(1 << bit_ix)};
	}
};

namespace Component
{
	enum class Id : unsigned
	{
		One,
		Two,
		Three,
		c4, c5, c6, c7, c8, c9, c10,
		// this special one will tells us how much bits we need
		Last_
	};
	
	static constexpr Id AllIds[] =
	{
		// well...
		Id::One, Id::Two, Id::Three, Id::c4, Id::c5, Id::c6, Id::c7, Id::c8, Id::c9, Id::c10
	};
	
	typedef EnumSet<unsigned(Id::Last_), Id, unsigned> Set;
}

int main()
{
	Component::Set cs {};
	cs[Component::Id::Two] = true;
	cs[Component::Id::c7] = true;
	for(Component::Id id : Component::AllIds)
		std::cout << unsigned(id) << " -> " << (cs[id] ? "true":"false") << std::endl;
}