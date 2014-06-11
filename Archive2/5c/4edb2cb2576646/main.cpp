#include <utility>

template <typename T>
struct X {
    template <typename... Args>
	T& init(Args&&... args) { value = new T(std::forward<Args>(args)...); return *value; }
	
	T& operator*() { return *value; }
	explicit operator bool() const { return value != nullptr; }

	T* value;
};

#define MAGICAL_INIT(var, ...)  ((var) ? *var : var.init(__VA_ARGS__))

int main()
{
	static X<int> x;
	MAGICAL_INIT(x); // don't pass any arguments
}