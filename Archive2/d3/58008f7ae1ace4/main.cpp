
#include <type_traits>
#include <utility>
#include <memory>

class CBaseClass {
public:
  virtual CBaseClass * clone() const {
    return new CBaseClass(*this);
  }
};

class CDerivedClass : public CBaseClass {
public:
  virtual CDerivedClass * clone() const {
    return new CDerivedClass(*this);
  }
};

class CMoreDerivedClass : public CDerivedClass {
public:
  virtual CMoreDerivedClass * clone() const {
    return new CMoreDerivedClass(*this);
  }
};

class CAnotherDerivedClass : public CBaseClass {
public:
  virtual CAnotherDerivedClass * clone() const {
    return new CAnotherDerivedClass(*this);
  }
};

// Clone factories

template <typename Class, typename T>
std::unique_ptr<Class> clone_unique(T&& source)
{
  static_assert(std::is_base_of<Class, typename std::decay<decltype(*source)>::type>::value,
    "can only clone for pointers to the target type (or base thereof)");
  return std::unique_ptr<Class>(source->clone());
}

template <typename Class, typename T>
std::shared_ptr<Class> clone_shared(T&& source)
{
  static_assert(std::is_base_of<Class, typename std::decay<decltype(*source)>::type>::value,
    "can only clone for pointers to the target type (or base thereof)");
  return std::shared_ptr<Class>(source->clone());
}

int main()
{
  std::unique_ptr<CDerivedClass> mdc(new CMoreDerivedClass()); // = std::make_unique<CMoreDerivedClass>();
  std::shared_ptr<CDerivedClass> cloned1 = clone_shared<CDerivedClass>(mdc);
  std::unique_ptr<CBaseClass> cloned2 = clone_unique<CBaseClass>(mdc);
  std::unique_ptr<CBaseClass> cloned3 = clone_unique<CBaseClass>(mdc);
  std::unique_ptr<CDerivedClass const> mdcConst(new CMoreDerivedClass()); // = std::make_unique<CMoreDerivedClass>();
  std::shared_ptr<CDerivedClass> clonedConst = clone_shared<CDerivedClass>(mdcConst);
  // these all generate compiler errors
  //std::unique_ptr<CAnotherDerivedClass> cloned4 = clone_unique<CAnotherDerivedClass>(mdc);
  //std::unique_ptr<CDerivedClass> cloned5 = clone_unique<CBaseClass>(mdc);
  //auto cloned6 = clone_unique<CMoreDerivedClass>(mdc);
}
