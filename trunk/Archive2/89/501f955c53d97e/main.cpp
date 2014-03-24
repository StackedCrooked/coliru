#include <iostream>
#include <thread>
#include <future>
#include <memory>

namespace later {
template<typename T> struct infix_tag {};

template<typename op, typename LHS>
struct partial {
  std::future<LHS>&& lhs;
};
// note: moves lhs!
template<typename LHS, typename Op>
partial<Op, LHS> operator*( std::future<LHS>& lhs, infix_tag<Op> ) {
  return { std::move(lhs) };
}
template<typename Op, typename LHS>
partial<Op, LHS> operator*( std::future<LHS>&& lhs, infix_tag<Op> ) {
  return { std::move(lhs) };
}
template<typename Op, typename LHS, typename RHS>
struct continue_t;

template<typename Op, typename LHS, typename RHS>
std::future< typename continue_t<Op, LHS, RHS>::type >
operator*( partial<Op, LHS>&& lhs, RHS&& rhs )
{
	return continue_t<Op, LHS, RHS>()( std::move(lhs.lhs), std::forward<RHS>(rhs) );
}

struct then_t:infix_tag<then_t> {};
static constexpr then_t then;

template<typename LHS, typename RHS>
struct continue_t<then_t, LHS, RHS> {
  typedef typename std::result_of< RHS( LHS ) >::type type;
  template<typename T, typename U>
  std::future<type> operator()( std::future<T>&& lhs_, U&& rhs_ ) const {
    auto lhs = std::make_shared<std::future<T>>( std::move(lhs_) );
    auto rhs = std::make_shared<typename std::remove_reference<U>::type>( std::forward<U>(rhs_) );
    return std::async( [lhs, rhs]()->type { return (*rhs)((*lhs).get()); } );
  }
};
template<typename RHS>
struct continue_t<then_t, void, RHS> {
  typedef typename std::result_of< RHS() >::type type;
  template<typename T, typename U>
  std::future<type> operator()( std::future<T>&& lhs_, U&& rhs_ ) const {
	auto lhs = std::make_shared<std::future<T>>( std::move(lhs_) );
	auto rhs = std::make_shared<typename std::remove_reference<U>::type>( std::forward<U>(rhs_) );
    return std::async( [lhs, rhs]()->type { lhs->get(); return (*rhs)(); } );
  }
};

struct as_well_t:infix_tag<as_well_t> {};
static constexpr as_well_t as_well;

template<typename LHS, typename RHS>
struct continue_t<as_well_t, LHS, RHS> {
  typedef std::tuple< LHS, typename std::result_of< RHS() >::type> type;
  template<typename T, typename U>
  std::future<type> operator()( std::future<T>&& lhs_, U&& rhs_ ) const {
    auto lhs = std::make_shared<std::future<T>>( std::move(lhs_) );
    auto rhs = std::make_shared<typename std::remove_reference<U>::type>( std::forward<U>(rhs_) );
    return std::async( [lhs, rhs]()->type {
        auto&& r = (*rhs)();
        return std::make_tuple((*lhs).get(), std::forward<decltype(r)>(r));
    });
  }
};
template<typename RHS>
struct continue_t<as_well_t, void, RHS> {
  typedef typename std::result_of< RHS() >::type type;
  template<typename T, typename U>
  std::future<type> operator()( std::future<T>&& lhs_, U&& rhs_ ) const {
    auto lhs = std::make_shared<std::future<T>>( std::move(lhs_) );
	auto rhs = std::make_shared<typename std::remove_reference<U>::type>( std::forward<U>(rhs_) );
    return std::async( [lhs, rhs]()->type {
        auto&& r = (*rhs)();
        lhs->get();
        return std::forward<decltype(r)>(r);
    });
  }
};

}

using later::then;
using later::as_well;

int main() {
	std::future<void> computation = std::async( [](){ return 7; })
	*then* [](int x) { return x+2; }
	*then* [](int x) { std::cout << x << "\n"; return x; }
    *as_well* []() { return 3; }
    *then* []( std::tuple<int, int> m ){ std::cout << std::get<0>(m) + std::get<1>(m) << "\n"; };
    computation.wait();
	// your code goes here
	return 0;
}