#include <iostream>

template <typename enum_type>
class FlagSet
{
    public:
        typedef typename std::underlying_type<enum_type>::type store_type;

        // Value constructor
        FlagSet(store_type value) : flags_(value)
        {
        }

        // Explicit conversion operator
        operator store_type() const
        {
            return flags_;
        }

    private:

        store_type flags_;
};

enum randomflag
{
    flag0 = 1 << 0,
	flag1 = 1 << 1,
	flag2 = 1 << 2
};

void foo(const FlagSet<randomflag>& flag)
{
	if (flag & flag0)
		std::cout << "flag 0" << std::endl;
	if (flag & flag1)
		std::cout << "flag 1" << std::endl;
	if (flag & flag2)
		std::cout << "flag 2" << std::endl;
}

int main()
{
	foo(flag0 | flag2);

	return 0;
}