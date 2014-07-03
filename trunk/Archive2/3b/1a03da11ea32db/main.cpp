class Handle {};

class Base
{
protected:		
	 virtual void load(const Handle &handle, const char * data) = 0;
public:
	 virtual ~Base() {}
	 void operator()(const Handle &handle, const char * data)
	 {
		 load(handle, data);
	 }
};

struct conversion_deducer {
    void const* thingy;
    
    template <typename T>
    operator T&() const {
        return *reinterpret_cast<T*>(thingy);
    }
};

template<class Func>
class Child : public Base
{
	Func loader;
protected:
	virtual void load(const Handle &handle, const char * data)
	{
		loader(handle, conversion_deducer { data });
	}
public:
	Child(Func f) : loader(f) {}
};

void f(Handle const&, int const&) {}

int main() {
    Child<decltype(f)*> c(f);
    Handle h;
    int i = 42;
    char const* p = reinterpret_cast<char const*>(&i);
    c(h, p);
}