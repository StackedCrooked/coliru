//http://stackoverflow.com/a/11812468/469659

#include <array>
#include <algorithm>
#include <initializer_list>
#include <type_traits>
#include <iostream>

//#define DONT_USE_EXPR_TEMPL

//===========================================================================

template <std::size_t N> class math_vector;
template <typename T> struct plus_op;


template <
  typename LeftExpr,
  typename BinaryOp,
  typename RightExpr
>
class math_vector_expr
{
  public:
    typedef typename std::remove_reference<LeftExpr>::type::value_type value_type;
  
    math_vector_expr() = delete;

    math_vector_expr(LeftExpr l, RightExpr r) :
      l_(std::forward<LeftExpr>(l)),
      r_(std::forward<RightExpr>(r))
    {
    }

    // Prohibit copying...
    math_vector_expr(math_vector_expr const&) = delete;
    math_vector_expr& operator =(math_vector_expr const&) = delete;

    // Allow moves...
    math_vector_expr(math_vector_expr&&) = default;
    math_vector_expr& operator =(math_vector_expr&&) = default;

    template <typename RE>
    auto operator +(RE&& re) const ->
      math_vector_expr<
        math_vector_expr<LeftExpr,BinaryOp,RightExpr> const&,
        plus_op<value_type>,
        decltype(std::forward<RE>(re))
      >
    {
      return
        math_vector_expr<
          math_vector_expr<LeftExpr,BinaryOp,RightExpr> const&,
          plus_op<value_type>,
          decltype(std::forward<RE>(re))
        >(*this, std::forward<RE>(re))
      ;
    }
    
    auto le() ->
      typename std::add_lvalue_reference<LeftExpr>::type
      { return l_; }

    auto le() const ->
      typename std::add_lvalue_reference<
        typename std::add_const<LeftExpr>::type
      >::type
      { return l_; }

    auto re() ->
      typename std::add_lvalue_reference<RightExpr>::type
      { return r_; }

    auto re() const ->
      typename std::add_lvalue_reference<
        typename std::add_const<RightExpr>::type
      >::type
      { return r_; }

    auto operator [](std::size_t index) const ->
      value_type
    {
      return BinaryOp::apply(le()[index], re()[index]);
    }

  private:
    LeftExpr l_;
    RightExpr r_;
};

//===========================================================================

template <typename T>
struct plus_op
{
  static T apply(T const& a, T const& b)
  {
    return a + b;
  }

  static T apply(T&& a, T const& b)
  {
    a += b;
    return std::move(a);
  }

  static T apply(T const& a, T&& b)
  {
    b += a;
    return std::move(b);
  }

  static T apply(T&& a, T&& b)
  {
    a += b;
    return std::move(a);
  }
};

//===========================================================================

template <std::size_t N>
class math_vector
{
  using impl_type = std::array<long double, N>;
  
  public:
    typedef typename impl_type::value_type value_type;
  
    math_vector()
    {
      using namespace std;
      fill(begin(v_), end(v_), impl_type{});
      std::cout << this << ": math_vector()" << endl;
    }

    math_vector(math_vector const& mv) noexcept
    {
      using namespace std;
      copy(begin(mv.v_), end(mv.v_), begin(v_));
      std::cout << this << ": math_vector(copy: " << &mv << ")" << endl;
    }

    math_vector(math_vector&& mv) noexcept
    {
      using namespace std;
      move(begin(mv.v_), end(mv.v_), begin(v_));
      std::cout << this << ": math_vector(move: " << &mv << ")" << endl;
    }

    math_vector(std::initializer_list<value_type> l)
    {
      using namespace std;
      copy(begin(l), end(l), begin(v_));
      std::cout << this << ": math_vector(initlist)" << endl;
    }

    math_vector& operator =(math_vector const& mv) noexcept
    {
      using namespace std;
      copy(begin(mv.v_), end(mv.v_), begin(v_));
      std::cout << this << ": math_vector op =(copy: " << &mv << ")" << endl;
      return *this;
    }

    math_vector& operator =(math_vector&& mv) noexcept
    {
      using namespace std;
      move(begin(mv.v_), end(mv.v_), begin(v_));
      std::cout << this << ": math_vector op =(move: " << &mv << ")" << endl;
      return *this;
    }

    ~math_vector()
    {
      using namespace std;
      std::cout << this << ": ~math_vector()" << endl;
    }

    void swap(math_vector& mv)
    {
      using namespace std;
      for (std::size_t i = 0; i<N; ++i)
        swap(v_[i], mv[i]);
    }

    auto operator [](std::size_t index) const
      -> value_type const&
    {
      return v_[index];
    }

    auto operator [](std::size_t index)
      -> value_type&
    {
      return v_[index];
    }

    math_vector& operator +=(math_vector const& b)
    {
      for (std::size_t i = 0; i<N; ++i)
        v_[i] += b[i];
      return *this;
    }

  #ifndef DONT_USE_EXPR_TEMPL

    template <typename LE, typename Op, typename RE>
    math_vector(math_vector_expr<LE,Op,RE>&& mve)
    {
      for (std::size_t i = 0; i < N; ++i)
        v_[i] = mve[i];
      std::cout << this << ": math_vector(expr: " << &mve << ")" << std::endl;
    }

    template <typename RightExpr>
    math_vector& operator =(RightExpr&& re)
    {
      for (std::size_t i = 0; i<N; ++i)
        v_[i] = re[i];
      return *this;
    }

    template <typename RightExpr>
    math_vector& operator +=(RightExpr&& re)
    {
      for (std::size_t i = 0; i<N; ++i)
        v_[i] += re[i];
      return *this;
    }

    template <typename RightExpr>
    auto operator +(RightExpr&& re) const ->
      math_vector_expr<
        math_vector const&,
        plus_op<value_type>,
        decltype(std::forward<RightExpr>(re))
      >
    {
      return
        math_vector_expr<
          math_vector const&,
          plus_op<value_type>,
          decltype(std::forward<RightExpr>(re))
        >(
          *this,
          std::forward<RightExpr>(re)
        )
      ;
    }

  #endif // #ifndef DONT_USE_EXPR_TEMPL

  private:
    impl_type v_;
};

//===========================================================================

template <std::size_t N>
inline void swap(math_vector<N>& a, math_vector<N>& b)
{
  a.swap(b);
}

//===========================================================================

#ifdef DONT_USE_EXPR_TEMPL

template <std::size_t N>
inline math_vector<N> operator +(
  math_vector<N> const& a,
  math_vector<N> const& b
)
{
  math_vector<N> retval(a);
  retval += b;
  return retval;
}

template <std::size_t N>
inline math_vector<N> operator +(
  math_vector<N>&& a,
  math_vector<N> const& b
)
{
  a += b;
  return std::move(a);
}

template <std::size_t N>
inline math_vector<N> operator +(
  math_vector<N> const& a,
  math_vector<N>&& b
)
{
  b += a;
  return std::move(b);
}

template <std::size_t N>
inline math_vector<N> operator +(
  math_vector<N>&& a,
  math_vector<N>&& b
)
{
  a += std::move(b);
  return std::move(a);
}

#endif // #ifdef DONT_USE_EXPR_TEMPL

//===========================================================================

template <std::size_t N>
std::ostream& operator <<(std::ostream& os, math_vector<N> const& mv)
{
  os << '(';
  for (std::size_t i = 0; i < N; ++i)
    os << mv[i] << ((i+1 != N) ? ',' : ')');
  return os;
}

//===========================================================================

int main()
{
  using namespace std;

  try
  {
    {
      cout << "CASE 1:\n";
      math_vector<3> a{1.0, 1.1, 1.2};
      math_vector<3> b{2.0, 2.1, 2.2};
      math_vector<3> c{3.0, 3.1, 3.2};
      math_vector<3> d{4.0, 4.1, 4.2};
      math_vector<3> result = a + b + c + d;
      cout << '[' << &result << "]: " << result << "\n";
    }
    cout << endl;
    {
      cout << "CASE 2:\n";
      math_vector<3> result =
        math_vector<3>{1.0, 1.1, 1.2} +
        math_vector<3>{2.0, 2.1, 2.2} +
        math_vector<3>{3.0, 3.1, 3.2} +
        math_vector<3>{4.0, 4.1, 4.2}
      ;
      cout << '[' << &result << "]: " << result << "\n";
    }
  }
  catch (...)
  {
    return 1;
  }
}

//===========================================================================