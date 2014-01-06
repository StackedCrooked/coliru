#include <iostream>
#include <type_traits>

#define BARK std::cerr << __PRETTY_FUNCTION__ << std::endl

template<typename T,             typename... Ts> struct has            : std::false_type {};
template<typename T,             typename... Ts> struct has<T,T,Ts...> : std::true_type {};
template<typename T, typename U, typename... Ts> struct has<T,U,Ts...> : has<T,Ts...> {};

template<typename T, typename A, template<class> class B, typename... Ts>
using conditional_has = typename std::conditional<has<T, Ts...>::value, A, B<T>>::type;

template<typename T, typename... Ts>
using enable_if_has = typename std::enable_if<has<T, Ts...>::value, int>::type;

struct NoexceptMove  {}; // OK
struct NoexceptCopy  {}; // OK
struct NoexceptCtor  {}; // OK

struct   PrivateDtor {}; // OK
struct ProtectedDtor {}; // OK

struct   VirtualDtor {}; // OK
struct      PureDtor {}; // not yet

struct    PublicCtor {}; // OK
struct   PrivateCtor {}; // OK
struct ProtectedCtor {}; // OK

struct PublicFunc    {}; // OK
struct ProtectedFunc {}; // OK
struct PrivateFunc   {}; // OK

template<typename T>
struct Dummy {
  private:
    struct X {};
  public:
    Dummy (X = {}) {}
    void func (X,...);
};

struct Base {
  Base () noexcept {BARK;}
  Base(int) noexcept {BARK;}
  Base(Base&&) noexcept {BARK;}
  Base(Base const&) noexcept {BARK;}

  void func () {BARK;}
};

struct VirtualDtorBase { virtual ~VirtualDtorBase () {}; };
struct PureDtorBase    { virtual ~PureDtorBase () = 0; }; inline PureDtorBase::~PureDtorBase () {}
struct DtorBase        { };

template<typename... Tags>
struct Obj : Base,

  std::conditional<
    has<VirtualDtor, Tags...>::value, VirtualDtorBase,
    typename std::conditional< has<PureDtor, Tags...>::value, PureDtorBase, DtorBase >::type
  >::type,

  Dummy<PublicFunc>, Dummy<ProtectedFunc>, Dummy<PrivateFunc>
{
  protected:
    template<typename T>
    using conditional_has = ::conditional_has<T, ::Base, ::Dummy, Tags...>;

    template<typename T, typename _>
    using enable_if_has = ::enable_if_has<T, _, Tags...>;

    template<typename T>
    using has = ::has<T, Tags...>;

  public:
    struct real_ctor_tag {};

    template<typename... Ts>
    Obj (real_ctor_tag, Ts&&... args) noexcept (has<NoexceptCtor>::value) : Base (std::forward<Ts> (args)...) {}
    Obj (Obj&&      rhs) noexcept (has<NoexceptMove>::value) : Base (std::move (rhs)) {}
    Obj (Obj const& rhs) noexcept (has<NoexceptCopy>::value) : Base (rhs) {}


  public:
    template<typename _ = int, enable_if_has<PublicCtor, _> = 0, typename... Ts>
    Obj (Ts&&... args) noexcept (noexcept (Obj (real_ctor_tag {}))): Obj (real_ctor_tag {}, std::forward<Ts> (args)...) { } 

  protected:
    template<typename _ = int, enable_if_has<ProtectedCtor, _> = 0, typename... Ts>
    Obj (Ts&&... args) noexcept (noexcept (Obj (real_ctor_tag {}))) : Obj (real_ctor_tag {}, std::forward<Ts> (args)...) { } 

  private:
    template<typename _ = int, enable_if_has<PrivateCtor, _> = 0, typename... Ts>
    Obj (Ts&&... args) noexcept (noexcept (Obj (real_ctor_tag {}))) : Obj (real_ctor_tag {}, std::forward<Ts> (args)...) { } 

  public:    using conditional_has<   PublicFunc>::func;
  protected: using conditional_has<ProtectedFunc>::func;
  private:   using conditional_has<  PrivateFunc>::func;
};


template<typename... Ts> struct PrivateDtorObj : Obj<Ts...> { using Obj<Ts...>::Obj; private: ~PrivateDtorObj () {}};
template<typename... Ts> struct  PublicDtorObj : Obj<Ts...> { using Obj<Ts...>::Obj; public: ~PublicDtorObj () {}};
template<typename... Ts> struct ProtectedDtorObj : Obj<Ts...> { using Obj<Ts...>::Obj; protected: ~ProtectedDtorObj () {}};

template<typename... Tags> 
using tracked = typename std::conditional<has<PrivateDtor, Tags...>::value, PrivateDtorObj<Tags...>, typename std::conditional<has<ProtectedDtor, Tags...>::value, ProtectedDtorObj<Tags...>, PublicDtorObj<Tags...>>::type>::type;

// -------------------------------

struct Derived : Obj<PrivateCtor, PureDtor> { };

int
main (int argc, char *argv[])
{

  static_assert (std::has_virtual_destructor<Obj<VirtualDtor>>::value, "");
  static_assert (std::is_nothrow_move_constructible<Obj<NoexceptMove>>::value, "");
  static_assert (std::is_nothrow_copy_constructible<Obj<NoexceptCopy>>::value, "");

  Derived x; // error
  tracked<ProtectedCtor, PrivateDtor> c; //error
}
