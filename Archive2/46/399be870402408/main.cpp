#include <iostream>

using namespace std;

template<int I>
struct pin_tag {};

//inputs
template<int N, class T0, class... VAR>
class inputs_base : public inputs_base<N + 1, VAR...>
{
protected:
   typedef inputs_base<N + 1, VAR...> base_type;
   using arg_type = T0;
   using base_type::_in;
   virtual void _in(T0 const& t, pin_tag<N>) = 0;
};

template<int N, class T0>
class inputs_base<N, T0>
{
protected:
   using arg_type = T0;
   virtual void _in(T0 const& t, pin_tag<N>) = 0;
};

template<class... VAR>
class inputs : public inputs_base<0, VAR...>
{
private:
   using inputs_type = inputs<VAR...>;
   using inputs_base_type = inputs_base<0, VAR...>;

   template <int N, class T = inputs_type>
   struct getter
   {
     using next_type = getter<N - 1, typename T::base_type>;
     using arg_type = typename next_type::arg_type;
     using current_type = typename next_type::current_type;
   };

   template <class T>
   struct getter<0, T>
   {
     using arg_type = typename T::arg_type;
     using current_type = T;
   };

   public:
   template<int N>
   using in_arg_type = typename getter<N>::arg_type;

   template<int N>
   void in(in_arg_type<N> const& t)
   {
		this->_in(t, pin_tag<N>());
//      getter<N>::current_type::_in(t, pin_tag<N>());
   }
};


class test : public inputs< int, bool >
{
protected:
   virtual void _in(int const& val, pin_tag<0>)
   {cout << val << endl;}
   virtual void _in(bool const& val, pin_tag<1>)
   {cout << val << endl;}
 };

int main()
{
   test t;
   t.in<0>(100500);
   t.in<1>(true);
}