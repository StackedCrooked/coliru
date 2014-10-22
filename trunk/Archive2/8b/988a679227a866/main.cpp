#include <vector>

class Copyable
{
public:
   Copyable() = default;

   Copyable(Copyable const& other)
      : m_int(other.m_int)
   {}

   Copyable& operator= (Copyable const& other)
   {
      m_int = other.m_int;
      return *this;
   }

   Copyable(Copyable&&) = delete;
   Copyable& operator= (Copyable&&) = delete;

private:
   int m_int = 100;
};

int main()
{
   std::vector<Copyable> objects;
   objects.push_back(Copyable{});
}