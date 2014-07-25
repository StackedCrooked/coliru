template <class T>
void ref(volatile T&) {}

template <class T>
void ref(volatile const T&) {}

template <class T>
void ref(const T&) {}

template <class T>
void ref(const T&&) = delete;

int&& a();
const int&& b();
volatile int&& c();
volatile const int&& d();

void test()
{
    ref(a());
	ref(b());
	ref(c());
	ref(d());
}
