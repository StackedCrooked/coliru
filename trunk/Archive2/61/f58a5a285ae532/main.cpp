#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <numeric>
#include <typeinfo>
#include <vector>

// mypointer

template<typename T>
class mypointer : public std::iterator<std::random_access_iterator_tag, T> {
public:
    using difference_type = std::ptrdiff_t;

    template<typename U>
	friend class mypointer;

	mypointer() : m_ptr(nullptr) {}
	mypointer(T* ptr) : m_ptr(ptr) {}
	template<typename U>
	mypointer(const mypointer<U>& x) : m_ptr(x.m_ptr) {}
	template<typename U>
	mypointer& operator=(const mypointer<U>& x) { m_ptr = x.m_ptr; return *this; }

	template<typename U>
	bool equal(const mypointer<U>& x) const { return m_ptr == x.m_ptr; }
	template<typename U>
	bool less(const mypointer<U>& x) const { return m_ptr < x.m_ptr; }

	T& operator*() const { return *to_pointer(); }
	T* operator->() const { return to_pointer(); }
	T& operator[](size_t i) const { return to_pointer()[i]; }

	mypointer& operator++() { ++m_ptr; return *this; }
	mypointer operator++(int) { mypointer temp(*this); ++(*this); return temp; }
	mypointer& operator--() { --m_ptr; return *this; }
	mypointer operator--(int) { mypointer temp(*this); --(*this); return temp; }

	mypointer& operator+=(difference_type x) { m_ptr += x; return *this; }
	mypointer& operator-=(difference_type x) { *this += -x; return *this; }
	
	template<typename U>
	difference_type operator-(const mypointer<U>& x) { return m_ptr - x.m_ptr; }

	operator T*() { return m_ptr; }

private:
	T* to_pointer() const { return m_ptr; }

	T* m_ptr = nullptr;
};

template<typename T, typename U>
inline bool operator==(const mypointer<T>& a, const mypointer<U>& b) {
	return a.equal(b);
}

template<typename T, typename U>
inline bool operator!=(const mypointer<T>& a, const mypointer<U>& b) {
	return !(a == b);
}

template<typename T, typename U>
bool operator<(const mypointer<T>& a, const mypointer<U>& b) {
	return a.equal(b);
}

template<typename T>
inline mypointer<T> operator+(mypointer<T> a, typename mypointer<T>::difference_type d) { a += d; return a; }

template<typename T>
inline mypointer<T> operator+(typename mypointer<T>::difference_type d, mypointer<T> a) { return a + d; }

template<typename T>
inline mypointer<T> operator-(mypointer<T> a, typename mypointer<T>::difference_type d) { a -= d; return a; }

// myallocator using mypointer

template<typename T>
struct myallocator {
	using value_type = T;
	using pointer = mypointer<T>;
	using const_pointer = mypointer<const T>;

	myallocator() = default;
	template<typename U>
	myallocator(const myallocator<U>&) {}

	pointer allocate(std::size_t n) {
		return pointer{ reinterpret_cast<T*>(new char[n]) };
	}
	void deallocate(pointer p, std::size_t) {
		delete[] &(*p);
	}
};

// Tests

template<typename T>
using myvector = std::vector<T, myallocator<T>>;

struct Foo { int value; };

struct Bar { virtual ~Bar() {} };
struct Baz : Bar {
	Baz() = default;
	Baz(int value_) : value(value_) {} 
	int value; 
};

std::ostream& operator<<(std::ostream& os, const Foo& foo) {
	os << foo.value;
	return os;
}

std::ostream& operator<<(std::ostream& os, const Baz& foo) {
	os << foo.value;
	return os;
}

template<typename Ptr, typename ConstPtr>
void testPointer() {
	using namespace std;
	using T = std::decay_t<decltype(*std::declval<Ptr>())>;

	T ts[10] = {};
	int i = 0;
	generate(begin(ts), end(ts), [&i]{return T{ i++ }; });
	Ptr myptr(&ts[0]);
	++myptr;
	cout << *myptr << endl;
	--myptr;
	cout << *myptr << endl;
	cout << *myptr++ << endl;
	cout << *myptr-- << endl;
	cout << myptr->value << endl;

	Ptr myptr2(&ts[0]);
	cout << boolalpha << (myptr == myptr2) << endl;
	cout << boolalpha << (++myptr == myptr2) << endl;

	myptr += 3;
	cout << *myptr << endl;

	cout << (myptr - myptr2) << endl;
	cout << *(myptr2 + 3) << endl;
	cout << *(3 + myptr2) << endl;
	cout << *(myptr - 3) << endl;
	cout << myptr2[5] << endl;
	myptr2[5] = T{ 12 };
	cout << myptr2[5] << endl;

	const ConstPtr myptr3(&ts[0]);
	cout << (myptr - myptr3) << endl;
	cout << *(myptr3 + 3) << endl;
	cout << *(3 + myptr3) << endl;
	cout << *((myptr3 + 2) - 1) << endl;
	cout << myptr3[5] << endl;
	cout << myptr3->value << endl;

	cout << boolalpha << (myptr3 == myptr2) << endl;
	cout << boolalpha << (myptr3 < myptr2) << endl;

	cout << "pointer: " << typeid(typename std::pointer_traits<Ptr>::pointer).name() << endl;
	cout << "element_type: " << typeid(typename std::pointer_traits<Ptr>::element_type).name() << endl;
	cout << "difference_type: " << typeid(typename std::pointer_traits<Ptr>::difference_type).name() << endl;
}

int main() {
	testPointer<Foo*, const Foo*>();
	testPointer<mypointer<Foo>, mypointer<const Foo>>();
	testPointer<mypointer<Baz>, mypointer<const Baz>>();
	Bar a;
	Baz b;
	mypointer<Bar> mpa(&b);
	mypointer<Baz> mpb(&b);
	std::cout << (mpb == mpa) << std::endl;
	std::cout << std::endl;

	myvector<int> myvec;
}
