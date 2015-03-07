// apply_test.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <boost/noncopyable.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/make_shared.hpp>

#define _TCHAR char
using namespace boost;

/* apply methods from
 * http://stackoverflow.com/questions/687490/how-do-i-expand-a-tuple-into-variadic-template-functions-arguments#answer-6454211
 */

// ------------- UTILITY---------------
template <int...> struct index_tuple {};

template <int I, typename IndexTuple, typename... Types> struct make_indexes_impl;

template <int I, int... Indexes, typename T, typename... Types>
struct make_indexes_impl<I, index_tuple<Indexes...>, T, Types...> {
    typedef typename make_indexes_impl<I + 1, index_tuple<Indexes..., I>, Types...>::type type;
};

template <int I, int... Indexes> struct make_indexes_impl<I, index_tuple<Indexes...> > {
    typedef index_tuple<Indexes...> type;
};

template <typename... Types> struct make_indexes : make_indexes_impl<0, index_tuple<>, Types...> {};

// ----------UNPACK TUPLE AND APPLY TO FUNCTION ---------
    template <class Ret, class Tuple, class... Args, int... Indexes>
    Ret apply_helper(Ret (*pf)(Args...), index_tuple<Indexes...>, Tuple&& tup) {
        return pf(std::forward<Args>(get<Indexes>(std::forward<Tuple>(tup)))...);
    }

    template <class Ret, class Tuple, class... Args> 
    Ret apply(Ret (*pf)(Args...), Tuple&& tup) {
        return apply_helper(pf, typename make_indexes<Args...>::type(), std::forward<Tuple>(tup));
    }

/* end of apply methods */

/* class iSelectable */
template <typename...> struct iSelectable;

template <class... Ts> struct iSelectable {
    template <typename T> static T select(Ts &&... params) { return T(std::forward<Ts>(params)...); }
};

/* selector_helper */
template <typename TT, class... Ts> struct selector_helper {
    static TT doSelect(Ts &&... params) { return iSelectable<Ts...>::template select<TT>(std::forward<Ts>(params)...); }
};

class postgres_database_impl : private boost::noncopyable,
                               public boost::enable_shared_from_this<postgres_database_impl> 
{
  public:
    template <typename T, typename... Ts> T select_(const std::string &sql) {
        boost::tuple<Ts...> tpl { -123, "fame", "something" };

        /* This is where my errors occur: */
        return apply(selector_helper<T, Ts...>::doSelect, tpl);
        return {123, "name", "something"};
    }
};

typedef boost::shared_ptr<postgres_database_impl> DatabaseImpl;

class Database : private boost::noncopyable {
  public:
    template <typename T, typename... Ts> T select_(const std::string &sql) { return impl_->select_<T, Ts...>(sql); }

  private:
    DatabaseImpl impl_ = boost::make_shared<postgres_database_impl>();
};

class User : public iSelectable<int, std::string, std::string> {
  public:
    User(int id, std::string const& name, std::string const& surname) {
        /* only for testing purposes */
        std::cout << id      << ", ";
        std::cout << name    << ", ";
        std::cout << surname << std::endl;
    }
};

int main() {
    Database db;
    User result =
        db.select_<User, int, std::string, std::string>("select id, email, name from credentials_tbl limit 1");

    (void)result;

    return 0;
}
