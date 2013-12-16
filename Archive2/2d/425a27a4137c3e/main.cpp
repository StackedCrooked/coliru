#include <boost/signals2.hpp>

typedef void(Sigature)(int);
typedef boost::signals2::signal<Sigature> Signal;
typedef Signal::slot_type                 SlotType;

class test{
    public:
        Signal sig;

        test() = default;
        test(const test& other) { *this = other; };

        test& operator=(test const& other) { sig.connect(other.sig); return *this; }

        void attach(SlotType const& f)   { sig.connect(f); }
        void trigger(int i) const        { sig(i); }
};

int main()
{
    test *a = new test(), *b = new test();
    a->attach([](int i) { std::cout << "subscribed to a:      " << i << "\n"; });
    a->attach([](int i) { std::cout << "also subscribed to a: " << i << "\n"; });

    std::cout << "Trigger via a:\n";
    a->trigger(42);

    (*b) = (*a);
    delete a;
    std::cout << "\nNow via b:\n";
    b->trigger(43);
}
