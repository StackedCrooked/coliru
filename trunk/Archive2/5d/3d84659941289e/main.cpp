#include <type_traits>
struct Foo { virtual ~Foo(){}};
struct FooBar : Foo { };
void f1(const Foo&, const Foo&) { }
void f2(const Foo&, const FooBar&) { }

template<typename B, typename D> struct Poly : std::false_type {};
template<typename B, typename D> struct Poly<const B&,const D&> : std::is_base_of<B,D> {};

template<int Rank, typename ...A> struct ArgCmp;

template<int Rank> struct ArgCmp<Rank> { enum { value = Rank }; };
template<int Rank, typename A>
struct ArgCmp<Rank,A>
{
   template<typename B> struct to {
      enum { value =
         Rank<0
            ? Rank
            : std::is_same<A,B>::value
               ? Rank
               : Poly<A,B>::value
                  ? Rank+1
                  : -1
      };
   };
};
template<int Rank, typename A, typename ...RA>
struct ArgCmp<Rank,A,RA...>
{
   template<typename B, typename ...RB> struct to {
      enum { value =
         Rank<0
            ? Rank
            : std::is_same<A,B>::value
               ? ArgCmp<Rank,RA...>::template to<RB...>::value
               : Poly<A,B>::value
                  ? 1+ArgCmp<Rank,RA...>::template to<RB...>::value
                  : -1
      };
   };
};

template<typename F,typename ...A> struct VF;
template<typename ...A,typename ...B> struct VF<void(A...),B...>
{
   enum { value = ArgCmp<0,A...>::template to<B...>::value };
};

#include <iostream>
int main() {
   enum { f1_score_f_f = VF<decltype(f1),const Foo   &,const Foo   &>::value };
   enum { f1_score_f_b = VF<decltype(f1),const Foo   &,const FooBar&>::value };
   enum { f1_score_b_f = VF<decltype(f1),const FooBar&,const Foo   &>::value };
   enum { f1_score_b_b = VF<decltype(f1),const FooBar&,const FooBar&>::value };
   enum { f2_score_f_f = VF<decltype(f2),const Foo   &,const Foo   &>::value };
   enum { f2_score_f_b = VF<decltype(f2),const Foo   &,const FooBar&>::value };
   enum { f2_score_b_f = VF<decltype(f2),const FooBar&,const Foo   &>::value };
   enum { f2_score_b_b = VF<decltype(f2),const FooBar&,const FooBar&>::value };
   std::cout << "\nf1_score_f_f = " << f1_score_f_f; 
   std::cout << "\nf1_score_f_b = " << f1_score_f_b; 
   std::cout << "\nf1_score_b_f = " << f1_score_b_f; 
   std::cout << "\nf1_score_b_b = " << f1_score_b_b; 
   std::cout << "\nf2_score_f_f = " << f2_score_f_f; 
   std::cout << "\nf2_score_f_b = " << f2_score_f_b; 
   std::cout << "\nf2_score_b_f = " << f2_score_b_f; 
   std::cout << "\nf2_score_b_b = " << f2_score_b_b; 
   std::cout << "\n";
}
