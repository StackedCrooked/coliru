#include <iostream>

class Base
{
protected:
    static void say_impl(Base* p)
    { std::cout << "Hello B(" <<p->b<< ")\n"; }
	
	struct vtable_t
	{
		using say_t = void(*)(Base*);
		say_t say;
	};
	static constexpr vtable_t Base_vtable = {say_impl};
	vtable_t const* vtable;
    
private:
    int b;
	
public:
	Base()
		: vtable(&Base_vtable)
		, b(21)
	{}
	Base(Base const& p)
		: vtable(&Base_vtable)
		, b(p.b)
	{}
	Base& operator=(Base const& p)
	{
		b = p.b;
		return *this;
	}
	
	void say()
	{
		vtable->say(this);
	}
};
Base::vtable_t const Base::Base_vtable;

class Derived : public Base
{
protected:
	static void say_impl(Base* p)
	{ std::cout << "Hello D(" <<static_cast<Derived&>(*p).d<< ")\n"; }
	
	static constexpr vtable_t Derived_vtable = {say_impl};
    
private:
    int d;
	
public:
	Derived()
		: Base()
		, d(42)
	{
		vtable = &Derived_vtable;
	}
	Derived(Derived const& p)
		: Base(p)
		, d(p.d)
	{
		vtable = &Derived_vtable;
	}
	Derived& operator=(Derived const& p)
	{
		static_cast<Base&>(*this) = p;
		d = p.d;
		return *this;
	}
    ~Derived()
    {
        vtable = &Base_vtable;
    }
};
Base::vtable_t const Derived::Derived_vtable;

int main() {
    Derived d;
    Derived* ptr = &d;
    Base* p = ptr;
    (*p).say();
    return 0;
}