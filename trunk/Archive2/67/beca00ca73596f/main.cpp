#include <memory>

template<typename T>
class foo
{
public:
   typedef void (T::*CallbackFn)();

   foo(T* mem, CallbackFn cb) : m_member(mem), m_cb(cb) {}

private:
   T* m_member;
   CallbackFn m_cb;
};

class another
{
private:
   void callback() {}

public:
   std::unique_ptr<foo<another>> f{new foo<another>(this, &another::callback)};
};

int main() {}