struct SomeType {};

class Base
{
    SomeType s;
public:
	operator const SomeType &() const { return s; }
};

class Derive : public Base
{
	int i = 0;
public:
	using Base::operator const SomeType &;
	operator const int&() const { return i; }
};

void fi(const int&) {}
void fs(const SomeType&) {}

int main ()
{
	Derive d;
	fi(d);
	fs(d);
}
