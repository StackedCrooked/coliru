template <class T>
void ref(T&) {}

template <class T>
void ref(volatile T&) {}

template <class T>
void ref(volatile const T&) {}

template <class T>
void ref(const T&) {}

template <class T>
void ref(const T&&) = delete;

// xvalues
int&& ax();
const int&& bx();
volatile int&& cx();
volatile const int&& dx();

// prvalues
int ap();
const int bp();
volatile int cp();
volatile const int dp();

void test()
{
    ref(ax());
    ref(bx());
    ref(cx());
    ref(dx());

    ref(ap());
    ref(bp());
    ref(cp());
    ref(dp());
}