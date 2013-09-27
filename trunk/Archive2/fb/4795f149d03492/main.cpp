#include <cstdlib>
#include <iostream>
#include <memory>

struct A : std::enable_shared_from_this<A> {
  using SharedPtr = std::shared_ptr<A>;
  using WeakPtr = std::weak_ptr<A>;

  A()  { std::cout << __PRETTY_FUNCTION__ << "\n"; }
  ~A() { std::cout << __PRETTY_FUNCTION__ << "\n"; }
};

int
main() {
  {
    std::unique_ptr<A::WeakPtr, void(*)(void*)>
        uwp(static_cast<A::WeakPtr*>(std::malloc(sizeof(A::WeakPtr))), std::free);
    A::WeakPtr* wp = uwp.get();

    {
      auto sp = std::make_shared<A>();
      new(wp) A::WeakPtr(sp);

      if (wp->lock())
        std::cout << "Locked\n";
      else
        std::cout << "Unlocked\n";
    }

    if (wp->lock())
      std::cerr << "EUNPOSSIBLE\n";
    else
      std::cout << "Unable to obtain lock\n";

    // Need the following 'using' statement because the following is invalid syntax:
    wp->A::WeakPtr::~WeakPtr();
    // using AWeakPtr = A::WeakPtr;
    // wp->~AWeakPtr();
    // Is there a way to call A::WeakPtr without the using statement?
  }
  std::cout << "memory held by uwp has been free(3)'ed\n";
}
