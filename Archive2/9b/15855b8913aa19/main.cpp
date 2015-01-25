#include <cassert>
#include <cstdio>
#include <type_traits>

template <typename T>
class Type
{
    template <typename... ArgsT>
	class Factory
	{
	public:
    #if 0
        template <typename U, typename = void>
        static U* Construct(ArgsT...)
        {
            assert("you fucked up");
            return nullptr;
        }
    #endif
        
        template <typename U, typename std::enable_if<std::is_constructible<U, ArgsT...>::value>::type>
        static U* Construct(ArgsT... args)
        {
            return new U(args...);
        }
	};

public:
	template <typename... ArgsT>
	T* CreateInstance(ArgsT... args)
	{
		return Factory<ArgsT...>::template Construct<T>(args...);
	}
};

class Bass {};
class Tuba : public Bass
{
    int _value;

public:
	Tuba(int value) : _value(value) {}

	void SoundOff()
	{
		printf("bah bah bah: %d\n", _value);
	}
};

int main()
{
	Type<Tuba> tubaType;
	Tuba* tuba = tubaType.CreateInstance(2);
	tuba->SoundOff();
	delete tuba;

	return 0;
}