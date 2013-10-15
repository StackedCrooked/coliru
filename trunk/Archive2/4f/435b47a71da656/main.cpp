#pragma once

#include <type_traits>

template <class AccessType>
struct FlagSet {
    typedef std::underlying_type<AccessType>::type MaskType;

	MaskType getMask() const { return flags.to_ulong(); }

	void setMask(MaskType newMask) {
		flags = std::bitset<NumBits> pattern(newMask);
	}

	bool getFlag(AccessType flag) {
		return flags.at(static_cast<size_t>(flag));
	}

	void setFlag(AccessType flag, bool newValue) {
		flags.at(static_cast<size_t>(flag), newValue);
	}

private:
	enum { NumBits = sizeof(MaskType)  * CHAR_BIT; };
	std::bitset<NumBits> flags;
};
