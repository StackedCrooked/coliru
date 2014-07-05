// Assertion stuff
#include <boost/mpl/assert.hpp>

// To invoke lambdas
#include <boost/mpl/apply.hpp>

// Required for while_
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>

// For testing stuff
#include <boost/mpl/int.hpp>
#include <boost/type_traits.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/list.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/equal.hpp>
#include <boost/mpl/reverse.hpp>

// while_ < Pred, Func, Val> - applies Func to Value while Pred on Value holds.

using namespace boost;
using mpl::placeholders::_1;
using mpl::placeholders::_2;

// while_ implementation:

template
<
  typename Pred,
  typename Func,
  typename Value
>
class while_ {
    
  template <typename F, typename X>
  struct lazy_apply;

  template<typename X>
  struct go : mpl::eval_if
    <
      typename mpl::apply<Pred, X>::type,
      lazy_apply<Func,X>,
      mpl::identity<X>
    > {};
    
  template <typename F, typename X>
  struct lazy_apply
  {
     typedef typename go< typename mpl::apply<F,X>::type>::type type;
  };

public:
  typedef typename go<Value>::type type;
};

// Numerical test:

typedef mpl::int_<0> zero;
typedef mpl::int_<5> five;

template<typename Num>
struct is_five : is_same<Num, five> {};

template<typename Num>
struct not_five : mpl::not_<is_five<Num> > {};

template<typename Num>
struct inc : mpl::int_<Num::value + 1> {};

typedef while_
  <
    not_five<_1>,
    inc<_1>,
    zero
  >::type five1;

BOOST_MPL_ASSERT((is_five<five1>));

// Actual test:

// We are trying to replace contents of the source list
// to the destination list in reversed order.

typedef mpl::list<char, short, int, float, double> Src;
typedef mpl::list<> Dst;

typedef mpl::pair
  <
    Src,
    Dst
  > init_task;

// 'reduce_task' removes the head of source list and
// prepends it to the destination list.
template<typename Task>
class reduce_task {
  // Pattern match task
  typedef typename Task::first  src;
  typedef typename Task::second dst;
  // Reduce
  typedef typename mpl::front<src>::type            head;
  typedef typename mpl::pop_front<src>::type        reduced_src;
  typedef typename mpl::push_front<dst, head>::type updated_dst;
  typedef mpl::pair
    <
      reduced_src,
      updated_dst
    > reduced_task;
public:
  typedef reduced_task type;
};

// Checks whether the task could be reduced:
template<typename Task>
struct can_reduce :
  mpl::not_
    <
      mpl::empty
        <
          typename Task::first
        >
    > {};

BOOST_MPL_ASSERT((can_reduce<init_task>));

// Let's check that after five reduce operations
// the task will became unreduciable:

typedef reduce_task<init_task>::type task1;
typedef reduce_task<task1>::type task2;
typedef reduce_task<task2>::type task3;
typedef reduce_task<task3>::type task4;
typedef reduce_task<task4>::type task5;
BOOST_MPL_ASSERT_NOT((can_reduce<task5>));

// We can't achieve the same result by using while_
// becauce the compilation with the code below
// uncommented leads to the long compilation error
// which says in short that the attempt to apply
// mpl::front to the empty list was detected.


typedef while_
  <
    can_reduce<_1>,
    reduce_task<_1>,
    init_task
  >::type reduced_task;
  
BOOST_MPL_ASSERT((mpl::equal<mpl::reverse<reduced_task::second>::type,init_task::first>));



// So, this means that mpl::eval_if do not
// actualy check the can_reduce<_1> predicate
// value and allows to continue caclulation
// at the moment where it should be stoped.

// Why is this going on?

int main() 
{
}
