typedef char (&yes)[1];
typedef char (&no)[2];

template <typename B, typename D>
struct Host
{
  operator B*() const;
  operator D*();
};

template <typename B, typename D>
struct is_base_of
{
  template <typename T> 
  static yes check(D*, T);
  static no check(B*, int);

  static const bool value = sizeof(check(Host<B,D>(), int())) == sizeof(yes);
};

class A {};
class B { constexpr operator A(); };

static_assert(!is_base_of<B,A>::value, "B is not a base of A");

int main(){}
