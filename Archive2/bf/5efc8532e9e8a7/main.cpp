#include <iostream>

struct S
{
   static void Lock() { std::cout << "Lock\n"; }
   static void Unlock() { std::cout << "Unlock\n"; }
};

template <typename T>
class AutoClassLock {
public:
    explicit AutoClassLock() { T::Lock(); }
    ~AutoClassLock() { T::Unlock(); }
};

int main(void)
{
    AutoClassLock<S> s;
}