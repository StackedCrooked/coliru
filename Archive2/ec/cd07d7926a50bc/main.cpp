#include <type_traits>

template <class AccessType>
struct FlagSet {
    typedef typename std::underlying_type<AccessType>::type MaskType;

	MaskType getMask() const { return flags.to_ulong(); }

	void setMask(MaskType newMask) { flags = std::bitset<NumBits>(newMask); }

	bool getFlag(AccessType flag) { return flags.at(static_cast<size_t>(flag)); }

	void setFlag(AccessType flag, bool newValue) {
		flags.set(static_cast<size_t>(flag), newValue);
	}

private:
	static const int NumBits = sizeof(MaskType) * CHAR_BIT;
	std::bitset<NumBits> flags;
};

enum class SomeFlags : short
{
    Flag_A,
	Flag_B,
	Flag_C,
	Flag_D,
	Flag_E,
	Flag_F,
	Flag_G,
	Flag_H,
	Flag_I
};

typedef FlagSet<SomeFlags> SomeSet;

int main(int argc, char* argv[])
{
	SomeSet ss;
	ss.setFlag(SomeFlags::Flag_C, true);
	std::cout << ss.getFlag(SomeFlags::Flag_C) << std::endl;

	short mask = 32;
	ss.setMask(mask);
    
    return 0;
}