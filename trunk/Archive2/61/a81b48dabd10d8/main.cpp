#include <tuple>
#include <type_traits>
namespace aks
{
    template<size_t N>
    struct variable
    {
        static const size_t dim = N+1;
        template<typename... Ts> auto operator()(Ts... ts) const 
        { 
            static_assert(dim <= sizeof...(Ts), "dimension insufficient"); return std::get<N>(std::make_tuple(ts...)); 
        }
    };

    template<typename T> struct is_variable                { enum{ value = false }; };
    template<size_t N>   struct is_variable< variable<N> > { enum{ value = true }; };

    template<typename T, typename U, typename Op>
    struct binary
    {
        static const size_t dim = T::dim > U::dim ? T::dim : U::dim;
        binary(T a, U b):t(a), u(b){}    
        template<typename... Args> auto operator()( Args... args ) const { static_assert(dim <= sizeof...(Args), "dimension insufficient"); return op(t(args...), u(args...)); }    
        template<typename... Args> auto operator()( Args... args )       { static_assert(dim <= sizeof...(Args), "dimension insufficient"); return op(t(args...), u(args...)); }
        T t; U u; Op op;
    };

    template<typename T>                          struct is_binary                 { enum{ value = false }; };
    template<typename T, typename U, typename Op> struct is_binary<binary<T,U,Op>> { enum{ value = true }; };

    template<typename T, typename Op>
    struct unary
    {
        static const size_t dim = T::dim;
        unary(T a):t(a){}    
        template<typename... Args> auto operator()( Args... args ) const { static_assert(dim <= sizeof...(Args), "dimension insufficient"); return op(t(args...)); }    
        template<typename... Args> auto operator()( Args... args )       { static_assert(dim <= sizeof...(Args), "dimension insufficient"); return op(t(args...)); }
        T t; Op op;
    };

    template<typename T>              struct is_unary              { enum{ value = false }; };
    template<typename T, typename Op> struct is_unary<unary<T,Op>> { enum{ value = true }; };

    template<typename T>
    struct constant
    {
        static const size_t dim = 0;
        typedef T value_type;
        constant(T a):t(a){}
        template<typename... Ts> auto operator()(Ts...) const { return t; }
        
        //operator T() { return t; }
        
        T t;
    };        
    
    template<typename T>
    auto make_constant(T t){ return constant<T>(t); }
    
    template<typename T> struct is_constant_type              { enum{ value = false }; };
    template<typename T> struct is_constant_type<constant<T>> { enum{ value = true }; };

    template<typename T> struct is_constant     : std::integral_constant<bool, !is_variable<T>::value && !is_binary<T>::value && !is_unary<T>::value> {};
    template<typename T> struct is_not_constant : std::integral_constant<bool, !is_constant<T>::value> {};
    
    template<typename T> struct is_independent     : std::integral_constant<bool, !is_variable<T>::value && !is_binary<T>::value && !is_unary<T>::value && !is_constant_type<T>::value> {};
    template<typename T> struct is_not_independent : std::integral_constant<bool, !is_independent<T>::value> {};
        
    #define DEFINE_BINARY_OP_INFIX(NAME, OP)                                                                                                                                                                             \
    struct NAME { template<typename T, typename U> auto operator()( T t, U u ) const { return t OP u; } };                                                                                                           \
    template<typename T, typename U> typename std::enable_if<is_not_independent<T>::value && is_not_independent<U>::value && is_not_constant<T>::value && is_not_constant<U>::value, binary<T,U, NAME >>::type operator OP ( T t, U u ) { return binary<T,U, NAME >(t,u); }                 \
    template<typename T, typename U> typename std::enable_if<is_not_constant<T>::value && is_independent<U>::value, binary<T,constant<U>, NAME >>::type operator OP ( T t, U u ) { return binary<T,constant<U>, NAME >(t,u); } \
    template<typename T, typename U> typename std::enable_if<is_independent<T>::value && is_not_constant<U>::value, binary<constant<T>,U, NAME >>::type operator OP ( T t, U u ) { return binary<constant<T>,U, NAME >(t,u); } \
    template<typename T, typename U> auto operator OP ( constant<T> t, constant<U> u ) { return make_constant(t.t OP u.t); } \
    template<typename T, typename U> auto operator OP ( T t, constant<U> u ) -> typename std::enable_if<is_not_independent<T>::value, decltype(( t OP u.t  ))>::type { return (t OP u.t  ); } \
    template<typename T, typename U> auto operator OP ( constant<T> t, U u ) -> typename std::enable_if<is_not_independent<U>::value, decltype(( t.t OP u  ))>::type { return (t.t OP u  ); } \
    template<typename T, typename U> auto operator OP ( T t, constant<U> u ) -> typename std::enable_if<is_independent<T>::value, decltype(make_constant( t OP u.t  ))>::type { return make_constant(t OP u.t  ); } \
    template<typename T, typename U> auto operator OP ( constant<T> t, U u ) -> typename std::enable_if<is_independent<U>::value, decltype(make_constant( t.t OP u  ))>::type { return make_constant(t.t OP u  ); } \
    
    DEFINE_BINARY_OP_INFIX( add, + );
    DEFINE_BINARY_OP_INFIX( sub, - );
    DEFINE_BINARY_OP_INFIX( mul, * );
    DEFINE_BINARY_OP_INFIX( dvd, / );
    DEFINE_BINARY_OP_INFIX( mod, % );
        
    struct negation { template<typename T> auto operator()( T t ){ return -t; } };
    template<typename T> typename std::enable_if<is_not_constant<T>::value, unary<T, negation >>::type operator - (T t){ return unary<T, negation >(t); }
}

#include <cmath>
namespace aks
{
    #define DEFINE_BINARY_OP_PREFIX(NAME, PREFIX_NAME, OP)                                                                                                                                                                  \
    struct NAME { template<typename T, typename U> auto operator()( T t, U u ) const { using namespace std; return PREFIX_NAME (t, u); } };                                                                                 \
    template<typename T, typename U> typename std::enable_if<is_not_constant<T>::value && is_not_constant<U>::value, binary<T,U, NAME >>::type operator OP ( T t, U u ) { return binary<T,U, NAME >(t,u); }                 \
    template<typename T, typename U> typename std::enable_if<is_not_constant<T>::value && is_constant<U>::value, binary<T,constant<U>, NAME >>::type operator OP ( T t, U u ) { return binary<T,constant<U>, NAME >(t,u); } \
    template<typename T, typename U> typename std::enable_if<is_constant<T>::value && is_not_constant<U>::value, binary<constant<T>,U, NAME >>::type operator OP ( T t, U u ) { return binary<constant<T>,U, NAME >(t,u); } \
    template<typename T, typename U> auto operator OP ( constant<T> t, constant<U> u ) { return make_constant(PREFIX_NAME(t.t,u.t)); } \
    template<typename T, typename U> auto operator OP ( T t, constant<U> u )           { return (PREFIX_NAME(t, u.t) ); } \
    template<typename T, typename U> auto operator OP ( constant<T> t, U u )           { return (PREFIX_NAME(t.t, u) ); }

    DEFINE_BINARY_OP_PREFIX(power, pow, ^);

    #define DEFINE_BINARY_FUNC_PREFIX(NAME, PREFIX_NAME, OP)                                                                                                                                                                  \
    struct NAME { template<typename T, typename U> auto operator()( T t, U u ) const { using namespace std; return PREFIX_NAME (t, u); } };                                                                                 \
    template<typename T, typename U> typename std::enable_if<is_not_constant<T>::value && is_not_constant<U>::value, binary<T,U, NAME >>::type OP ( T t, U u ) { return binary<T,U, NAME >(t,u); }                 \
    template<typename T, typename U> typename std::enable_if<is_not_constant<T>::value && is_constant<U>::value, binary<T,constant<U>, NAME >>::type OP ( T t, U u ) { return binary<T,constant<U>, NAME >(t,u); } \
    template<typename T, typename U> typename std::enable_if<is_constant<T>::value && is_not_constant<U>::value, binary<constant<T>,U, NAME >>::type OP ( T t, U u ) { return binary<constant<T>,U, NAME >(t,u); } \
    template<typename T, typename U> auto OP ( constant<T> t, constant<U> u ) { return make_constant(PREFIX_NAME(t.t,u.t)); } \
    template<typename T, typename U> auto OP ( T t, constant<U> u )           { return (PREFIX_NAME(t, u.t) ); } \
    template<typename T, typename U> auto OP ( constant<T> t, U u )           { return (PREFIX_NAME(t.t, u) ); } 

    DEFINE_BINARY_FUNC_PREFIX(arc_tangent_2, atan2, atan2);

    #define DEFINE_UNARY_FUNC(NAME, PREFIX_NAME, CALL_NAME)                                                                                       \
    struct NAME { template<typename T> auto operator()( T t ) { using namespace std; return PREFIX_NAME(t); } };                                \
    template<typename T> typename std::enable_if<is_not_constant<T>::value, unary<T, NAME >>::type CALL_NAME (T t){ return unary<T, NAME >(t); }\
    template<typename T> auto CALL_NAME( constant<T> t ){ using namespace std; return make_constant(PREFIX_NAME(t.t)); }

    DEFINE_UNARY_FUNC(cosine , cos, cos); //
    DEFINE_UNARY_FUNC(sine   , sin, sin); //
    DEFINE_UNARY_FUNC(tangent, tan, tan); //
    DEFINE_UNARY_FUNC(arc_cosine , acos, acos); //
    DEFINE_UNARY_FUNC(arc_sine   , asin, asin); //
    DEFINE_UNARY_FUNC(arc_tangent, atan, atan); //
    DEFINE_UNARY_FUNC(hyperbolic_cosine , cosh, cosh); //
    DEFINE_UNARY_FUNC(hyperbolic_sine   , sinh, sinh); //
    DEFINE_UNARY_FUNC(hyperbolic_tangent, tanh, tanh);
    DEFINE_UNARY_FUNC(hyperbolic_arc_cosine , acosh, acosh); //
    DEFINE_UNARY_FUNC(hyperbolic_arc_sine   , asinh, asinh); //
    DEFINE_UNARY_FUNC(hyperbolic_arc_tangent, atanh, atanh); //
    DEFINE_UNARY_FUNC(exponential        , exp, exp); //
    DEFINE_UNARY_FUNC(logarithm_natural  , log, log);
    DEFINE_UNARY_FUNC(logarithm_common   , log10, log10);
    DEFINE_UNARY_FUNC(sq_root , sqrt, sqrt); //
    DEFINE_UNARY_FUNC(cube_root , cbrt, cbrt); //
    DEFINE_UNARY_FUNC(absolute_value , abs, abs); //
}

namespace aks
{
    template<typename T>
    auto derivative(T);
    
    template<typename T>
    auto derivative( constant<T> ) { return constant<int>(0); }
    
    template<size_t N>
    auto derivative( variable<N> ) { return constant<int>(1); }
    
    template<typename T, typename U>
    auto derivative( binary<T,U,add> b ) { return derivative(b.t) + derivative(b.u); }
    
    template<typename T, typename U>
    auto derivative( binary<T,constant<U>,add> b ) { return derivative(b.t); }    
    
    template<typename T, typename U>
    auto derivative( binary<constant<T>,U,add> b ) { return derivative(b.u); }
        
    template<typename T, typename U>
    auto derivative( binary<T,U,sub> b ) { return derivative(b.t) - derivative(b.u); }
    
    template<typename T, typename U>
    auto derivative( binary<T,constant<U>,sub> b ) { return derivative(b.t); }    
    
    template<typename T, typename U>
    auto derivative( binary<constant<T>,U,sub> b ) { return make_constant(-1) * derivative(b.u); }
    
    template<typename T, typename U>
    auto derivative( binary<T,U,mul> b ) { return (derivative(b.t)*b.u) + (derivative(b.u)*b.t);  }
    
    template<size_t N, typename U>
    auto derivative( binary<variable<N>,U,mul> b ) { return (b.u) + (derivative(b.u)*b.t);  }  

    template<typename T, size_t N>
    auto derivative( binary<T,variable<N>,mul> b ) { return (derivative(b.t)*b.u) + (b.t);  }
    
    template<size_t T, size_t N>
    auto derivative( binary<variable<T>,variable<N>,mul> b ) { return (b.u) + (b.t);  }
    
    template<typename T, typename U>
    auto derivative( binary<T,U,dvd> b ) { return (derivative(b.t)*b.u - derivative(b.u)*b.t)/(b.u*b.u); }  

    template<typename T>
    auto derivative( unary<T, negation> u ) { return -1*derivative(u.t); }
    
    template<size_t N>
    auto derivative( unary<variable<N>, negation> u ) { return constant<int>(-1); }
}

namespace aks
{
    template<typename T>
    auto derivative( unary<T, cosine> u ) { return -sin(u.t)*derivative(u.t); }
    
    template<typename T>
    auto derivative( unary<T, sine> u ) { return cos(u.t)*derivative(u.t); }
    
    template<typename T>
    auto derivative( unary<T, tangent> u ) { return (1 + tan(u.t)*tan(u.t))*derivative(u.t); }
    
    template<typename T>
    auto derivative( unary<T, arc_cosine> u ) { return (-(1/sqrt(1-u.t*u.t)))*derivative(u.t); }
    
    template<typename T>
    auto derivative( unary<T, arc_sine> u ) { return ((1/sqrt(1-u.t*u.t)))*derivative(u.t); }
    
    template<typename T>
    auto derivative( unary<T, arc_tangent> u ) { return (1/(1+u.t*u.t))*derivative(u.t); }
    
    template<typename T>
    auto derivative( unary<T, hyperbolic_cosine> u ) { return sinh(u.t)*derivative(u.t); }
    
    template<typename T>
    auto derivative( unary<T, hyperbolic_sine> u ) { return cosh(u.t)*derivative(u.t); }
    
    template<typename T>
    auto derivative( unary<T, hyperbolic_arc_cosine> u ) { return (1/sqrt(u.t*u.t + 1))*derivative(u.t); }
    
    template<typename T>
    auto derivative( unary<T, hyperbolic_arc_sine> u ) { return (1/sqrt(u.t*u.t - 1))*derivative(u.t); }
    
    template<typename T>
    auto derivative( unary<T, hyperbolic_arc_tangent> u ) { return (1/(1- u.t*u.t))*derivative(u.t); }
    
    template<typename T>
    auto derivative( unary<T, exponential> u ) { return u*derivative(u.t); }
    
    template<typename T>
    auto derivative( unary<T, sq_root> u ) { return (0.5 * (1.0/u))*derivative(u.t); }
    
    template<typename T>
    auto derivative( unary<T, cube_root> u ) { return (1.0/(3*cbrt(u.t*u.t)))*derivative(u.t); }
    
    template<typename T>
    auto derivative( unary<T, absolute_value> u ) { return (u.t/u)*derivative(u.t); }    
    
//

    template<size_t N>
    auto derivative( unary<variable<N>, cosine> u ) { return -sin(u.t); }
    
    template<size_t N>
    auto derivative( unary<variable<N>, sine> u ) { return cos(u.t); }
    
    template<size_t N>
    auto derivative( unary<variable<N>, tangent> u ) { return (1 + tan(u.t)*tan(u.t)); }
    
    template<size_t N>
    auto derivative( unary<variable<N>, arc_cosine> u ) { return (-(1/sqrt(1-u.t*u.t))); }
    
    template<size_t N>
    auto derivative( unary<variable<N>, arc_sine> u ) { return ((1/sqrt(1-u.t*u.t))); }
    
    template<size_t N>
    auto derivative( unary<variable<N>, arc_tangent> u ) { return (1/(1+u.t*u.t)); }
    
    template<size_t N>
    auto derivative( unary<variable<N>, hyperbolic_cosine> u ) { return sinh(u.t); }
    
    template<size_t N>
    auto derivative( unary<variable<N>, hyperbolic_sine> u ) { return cosh(u.t); }
    
    template<size_t N>
    auto derivative( unary<variable<N>, hyperbolic_arc_cosine> u ) { return (1/sqrt(u.t*u.t + 1)); }
    
    template<size_t N>
    auto derivative( unary<variable<N>, hyperbolic_arc_sine> u ) { return (1/sqrt(u.t*u.t - 1)); }
    
    template<size_t N>
    auto derivative( unary<variable<N>, hyperbolic_arc_tangent> u ) { return (1/(1- u.t*u.t)); }
    
    template<size_t N>
    auto derivative( unary<variable<N>, exponential> u ) { return u; }
    
    template<size_t N>
    auto derivative( unary<variable<N>, sq_root> u ) { return (0.5 * (1.0/u)); }
    
    template<size_t N>
    auto derivative( unary<variable<N>, cube_root> u ) { return (1.0/(3*cbrt(u.t*u.t))); }
    
    template<size_t N>
    auto derivative( unary<variable<N>, absolute_value> u ) { return (u.t/u); }      
}

namespace aks
{
    template<typename T, size_t M>
    struct depends_on_dim;
    
    template<size_t N, size_t M>
    struct depends_on_dim<variable<N>, M>
    {
        enum{ value = M==N };
    };
    
    template<typename T, size_t M>
    struct depends_on_dim<constant<T>, M>
    {
        enum{ value = false };
    };
    
    template<typename T, typename U, typename Op, size_t M>
    struct depends_on_dim<binary<T,U,Op>, M>
    {
        enum{ value = depends_on_dim<T, M>::value || depends_on_dim<U, M>::value };
    };
    
    template<typename T, typename Op, size_t M>
    struct depends_on_dim<unary<T,Op>, M>
    {
        enum{ value = depends_on_dim<T, M>::value };
    };
    
    template<typename T, size_t N>
    constexpr bool depends_on(T t, aks::variable<N>)
    {
        return aks::depends_on_dim<T, N>::value;
    }
    
    template<bool B>
    struct get_return
    {
        template<typename T, typename U>
        static auto apply(T t, U){ return t; }
    };
    
    template<>
    struct get_return<false>
    {
        template<typename T, typename U>
        static auto apply(T, U u){ return u; }
    };
}

namespace aks
{
    template<typename T, size_t D>
    auto differentiate(T, variable<D>);
    
    template<typename T, size_t N>
    auto differentiate( constant<T>, variable<N> ) { return constant<int>(0); }
    
    template<size_t M, size_t N>
    auto differentiate( variable<M>, variable<N> ) { return constant<int>(M==N ? 1 : 0); }
    
    template<typename T, typename U, size_t N>
    auto differentiate( binary<T,U,add> b, variable<N> v) { return get_return<!depends_on_dim<decltype(b), N>::value>::apply(constant<int>(0), differentiate(b.t,v) + differentiate(b.u,v)); }
    
    template<typename T, typename U, size_t N>
    auto differentiate( binary<T,constant<U>,add> b, variable<N> v) { return get_return<!depends_on_dim<decltype(b), N>::value>::apply(constant<int>(0),  differentiate(b.t,v)); }    
    
    template<typename T, typename U, size_t N>
    auto differentiate( binary<constant<T>,U,add> b, variable<N> v) { return get_return<!depends_on_dim<decltype(b), N>::value>::apply(constant<int>(0),  differentiate(b.u,v)); }
        
    template<typename T, typename U, size_t N>
    auto differentiate( binary<T,U,sub> b, variable<N> v) { return get_return<!depends_on_dim<decltype(b), N>::value>::apply(constant<int>(0),  differentiate(b.t,v) - differentiate(b.u,v)); }
    
    template<typename T, typename U, size_t N>
    auto differentiate( binary<T,constant<U>,sub> b, variable<N> v) { return get_return<!depends_on_dim<decltype(b), N>::value>::apply(constant<int>(0),  differentiate(b.t,v)); }    
    
    template<typename T, typename U, size_t N>
    auto differentiate( binary<constant<T>,U,sub> b, variable<N> v) { return get_return<!depends_on_dim<decltype(b), N>::value>::apply(constant<int>(0),  make_constant(-1) * differentiate(b.u,v)); }
    
    template<typename T, typename U, size_t N>
    auto differentiate( binary<T,U,mul> b, variable<N> v) { return get_return<!depends_on_dim<decltype(b), N>::value>::apply(constant<int>(0),  (differentiate(b.t,v)*b.u) + (differentiate(b.u,v)*b.t));  }
    
    //template<size_t N, typename U, size_t D>
    //auto differentiate( binary<variable<N>,U,mul> b, variable<D> v) { return get_return<!depends_on_dim<decltype(b), D>::value>::apply(constant<int>(0),  (b.u) + (differentiate(b.u)*b.t));  }  
    //
    //template<typename T, size_t N, size_t D>
    //auto differentiate( binary<T,variable<N>,mul> b, variable<D> v) { return get_return<!depends_on_dim<decltype(b), D>::value>::apply(constant<int>(0),  (differentiate(b.t)*b.u) + (b.t));  }
    //
    //template<size_t T, size_t N, size_t D>
    //auto differentiate( binary<variable<T>,variable<N>,mul> b, variable<D> v) { return get_return<!depends_on_dim<decltype(b), D>::value>::apply(constant<int>(0),  (b.u) + (b.t));  }
    
    template<typename T, typename U, size_t N>
    auto differentiate( binary<T,U,dvd> b, variable<N> v) { return get_return<!depends_on_dim<decltype(b), N>::value>::apply(constant<int>(0),  (differentiate(b.t,v)*b.u - differentiate(b.u,v)*b.t)/(b.u*b.u)); }  

    template<typename T, size_t N>
    auto differentiate( unary<T, negation> u, variable<N> v) { return get_return<!depends_on_dim<decltype(u), N>::value>::apply(constant<int>(0),  -1*differentiate(u.t,v)); }
    
    template<size_t N, size_t D>
    auto differentiate( unary<variable<N>, negation> u, variable<D> v) { return get_return<!depends_on_dim<decltype(u), D>::value>::apply(constant<int>(0),  constant<int>(-1)); }
}

namespace aks
{
    template<typename T, size_t D>
    auto differentiate( unary<T, cosine> u, variable<D> v ) { return get_return<!depends_on_dim<decltype(u), D>::value>::apply(constant<int>(0),   -sin(u.t)*differentiate(u.t,v)); }
    
    template<typename T, size_t D>
    auto differentiate( unary<T, sine> u, variable<D> v ) { return get_return<!depends_on_dim<decltype(u), D>::value>::apply(constant<int>(0),   cos(u.t)*differentiate(u.t,v)); }
    
    template<typename T, size_t D>
    auto differentiate( unary<T, tangent> u, variable<D> v ) { return get_return<!depends_on_dim<decltype(u), D>::value>::apply(constant<int>(0),   (1 + tan(u.t)*tan(u.t))*differentiate(u.t,v)); }
    
    template<typename T, size_t D>
    auto differentiate( unary<T, arc_cosine> u, variable<D> v ) { return get_return<!depends_on_dim<decltype(u), D>::value>::apply(constant<int>(0),   (-(1/sqrt(1-u.t*u.t)))*differentiate(u.t,v)); }
    
    template<typename T, size_t D>
    auto differentiate( unary<T, arc_sine> u, variable<D> v ) { return get_return<!depends_on_dim<decltype(u), D>::value>::apply(constant<int>(0),   ((1/sqrt(1-u.t*u.t)))*differentiate(u.t,v)); }
    
    template<typename T, size_t D>
    auto differentiate( unary<T, arc_tangent> u, variable<D> v ) { return get_return<!depends_on_dim<decltype(u), D>::value>::apply(constant<int>(0),   (1/(1+u.t*u.t))*differentiate(u.t,v)); }
    
    template<typename T, size_t D>
    auto differentiate( unary<T, hyperbolic_cosine> u, variable<D> v ) { return get_return<!depends_on_dim<decltype(u), D>::value>::apply(constant<int>(0),   sinh(u.t)*differentiate(u.t,v)); }
    
    template<typename T, size_t D>
    auto differentiate( unary<T, hyperbolic_sine> u, variable<D> v ) { return get_return<!depends_on_dim<decltype(u), D>::value>::apply(constant<int>(0),   cosh(u.t)*differentiate(u.t,v)); }
    
    template<typename T, size_t D>
    auto differentiate( unary<T, hyperbolic_arc_cosine> u, variable<D> v ) { return get_return<!depends_on_dim<decltype(u), D>::value>::apply(constant<int>(0),   (1/sqrt(u.t*u.t + 1))*differentiate(u.t,v)); }
    
    template<typename T, size_t D>
    auto differentiate( unary<T, hyperbolic_arc_sine> u, variable<D> v ) { return get_return<!depends_on_dim<decltype(u), D>::value>::apply(constant<int>(0),   (1/sqrt(u.t*u.t - 1))*differentiate(u.t,v)); }
    
    template<typename T, size_t D>
    auto differentiate( unary<T, hyperbolic_arc_tangent> u, variable<D> v ) { return get_return<!depends_on_dim<decltype(u), D>::value>::apply(constant<int>(0),   (1/(1- u.t*u.t))*differentiate(u.t,v)); }
    
    template<typename T, size_t D>
    auto differentiate( unary<T, exponential> u, variable<D> v ) { return get_return<!depends_on_dim<decltype(u), D>::value>::apply(constant<int>(0),   u*differentiate(u.t,v)); }
    
    template<typename T, size_t D>
    auto differentiate( unary<T, sq_root> u, variable<D> v ) { return get_return<!depends_on_dim<decltype(u), D>::value>::apply(constant<int>(0),   (0.5 * (1.0/u))*differentiate(u.t,v)); }
    
    template<typename T, size_t D>
    auto differentiate( unary<T, cube_root> u, variable<D> v ) { return get_return<!depends_on_dim<decltype(u), D>::value>::apply(constant<int>(0),   (1.0/(3*cbrt(u.t*u.t)))*differentiate(u.t,v)); }
    
    template<typename T, size_t D>
    auto differentiate( unary<T, absolute_value> u, variable<D> v ) { return get_return<!depends_on_dim<decltype(u), D>::value>::apply(constant<int>(0),   (u.t/u)*differentiate(u.t,v)); }    
    
//

    template<size_t N, size_t D>
    auto differentiate( unary<variable<N>, cosine> u, variable<D> v ) { return get_return<!(N==D)>::apply(constant<int>(0), -sin(u.t)); }
    
    template<size_t N, size_t D>
    auto differentiate( unary<variable<N>, sine> u, variable<D> v ) { return get_return<!(N==D)>::apply(constant<int>(0), cos(u.t)); }
    
    template<size_t N, size_t D>
    auto differentiate( unary<variable<N>, tangent> u, variable<D> v ) { return get_return<!(N==D)>::apply(constant<int>(0), (1 + tan(u.t)*tan(u.t))); }
    
    template<size_t N, size_t D>
    auto differentiate( unary<variable<N>, arc_cosine> u, variable<D> v ) { return get_return<!(N==D)>::apply(constant<int>(0), (-(1/sqrt(1-u.t*u.t)))); }
    
    template<size_t N, size_t D>
    auto differentiate( unary<variable<N>, arc_sine> u, variable<D> v ) { return get_return<!(N==D)>::apply(constant<int>(0), ((1/sqrt(1-u.t*u.t)))); }
    
    template<size_t N, size_t D>
    auto differentiate( unary<variable<N>, arc_tangent> u, variable<D> v ) { return get_return<!(N==D)>::apply(constant<int>(0), (1/(1+u.t*u.t))); }
    
    template<size_t N, size_t D>
    auto differentiate( unary<variable<N>, hyperbolic_cosine> u, variable<D> v ) { return get_return<!(N==D)>::apply(constant<int>(0), sinh(u.t)); }
    
    template<size_t N, size_t D>
    auto differentiate( unary<variable<N>, hyperbolic_sine> u, variable<D> v ) { return get_return<!(N==D)>::apply(constant<int>(0), cosh(u.t)); }
    
    template<size_t N, size_t D>
    auto differentiate( unary<variable<N>, hyperbolic_arc_cosine> u, variable<D> v ) { return get_return<!(N==D)>::apply(constant<int>(0), (1/sqrt(u.t*u.t + 1))); }
    
    template<size_t N, size_t D>
    auto differentiate( unary<variable<N>, hyperbolic_arc_sine> u, variable<D> v ) { return get_return<!(N==D)>::apply(constant<int>(0), (1/sqrt(u.t*u.t - 1))); }
    
    template<size_t N, size_t D>
    auto differentiate( unary<variable<N>, hyperbolic_arc_tangent> u, variable<D> v ) { return get_return<!(N==D)>::apply(constant<int>(0), (1/(1- u.t*u.t))); }
    
    template<size_t N, size_t D>
    auto differentiate( unary<variable<N>, exponential> u, variable<D> v ) { return get_return<!(N==D)>::apply(constant<int>(0), u); }
    
    template<size_t N, size_t D>
    auto differentiate( unary<variable<N>, sq_root> u, variable<D> v ) { return get_return<!(N==D)>::apply(constant<int>(0), (0.5 * (1.0/u))); }
    
    template<size_t N, size_t D>
    auto differentiate( unary<variable<N>, cube_root> u, variable<D> v ) { return get_return<!(N==D)>::apply(constant<int>(0), (1.0/(3*cbrt(u.t*u.t)))); }
    
    template<size_t N, size_t D>
    auto differentiate( unary<variable<N>, absolute_value> u, variable<D> v ) { return get_return<!(N==D)>::apply(constant<int>(0), (u.t/u)); }      
}

// http://goo.gl/NUpsOt

#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <type_traits>
#include <typeinfo>

#include <cstdlib>
#include <memory>
#include <cxxabi.h>

std::string demangle(const char* name) {

    int status = -4; // some arbitrary value to eliminate the compiler warning

    // enable c++11 by passing the flag -std=c++11 to g++
    std::unique_ptr<char, void(*)(void*)> res {
        abi::__cxa_demangle(name, NULL, NULL, &status),
        std::free
    };

    return (status==0) ? res.get() : name ;
}

template<typename T>
constexpr size_t get_dim(T)
{
    return T::dim;
}

#include <tuple>

template<typename... Ts>
auto functions(Ts... ts)
{
    return std::make_tuple(ts...);
}

namespace detail
{
    template<int... Is>
    struct seq { };

    template<int N, int... Is>
    struct gen_seq : gen_seq<N - 1, N - 1, Is...> { };

    template<int... Is>
    struct gen_seq<0, Is...> : seq<Is...> { };

    template<typename T, typename F, int... Is>
    void for_each(T&& t, F f, seq<Is...>)
    {
        auto l = { (f(std::get<Is>(t)), 0)... };
    }
}

template<typename... Ts, typename F>
void for_each_in_tuple(std::tuple<Ts...> const& t, F f)
{
    detail::for_each(t, f, detail::gen_seq<sizeof...(Ts)>());
}    

template<typename T, int... Is, typename... As >
auto eval( T t, detail::seq<Is...>, As... as )
{
    return std::make_tuple( std::get<Is>(t)(as...)... );
}

template<typename... Ts, typename... As>
auto evaluate( std::tuple<Ts...> t, As... ts )
{
    return eval(t, detail::gen_seq<sizeof...(Ts)>(), ts...);
}

template<size_t N, size_t... Ns>
struct Max
{
    enum{ value = N > Max<Ns...>::value ? N : Max<Ns...>::value };
};

template<size_t N>
struct Max<N>
{
    enum{ value = N };
};

template<size_t... Is>
struct sz_seq { };

template<int N, size_t... Is>
struct sz_gen_seq : sz_gen_seq<N - 1, N - 1, Is...> { };

template<size_t... Is>
struct sz_gen_seq<0, Is...> : sz_seq<Is...> { };

template<typename F, size_t... Ns>
auto jacobian_detail2(F f, sz_seq<Ns...>)
{
    return std::make_tuple(aks::differentiate(f, aks::variable<Ns>())...);
}

template<typename... Fs, size_t... Ns>
auto jacobian_detail(sz_seq<Ns...>, Fs... fs)
{
    return std::make_tuple( jacobian_detail2(fs,sz_seq<Ns...>())... );
}

template<typename... Fs>
auto jacobian(Fs... fs)
{
    return jacobian_detail(sz_gen_seq<Max<decltype(fs)::dim...>::value>(), fs...);
}

template<size_t FN, size_t VN, typename... Ts>
auto get_jacobian_element(std::tuple<Ts...> const& t)
{
    return std::get<VN>(std::get<FN>(t));
}

#include <vector>
#include <cstddef>
#include <tuple>
#include <type_traits>
#include <utility>

template<size_t N>
struct Apply {
    template<typename F, typename T, typename... A>
    static inline auto apply(F && f, T && t, A &&... a) {
        return Apply<N-1>::apply(::std::forward<F>(f), ::std::forward<T>(t),
            ::std::get<N-1>(::std::forward<T>(t)), ::std::forward<A>(a)...
        );
    }
};

template<>
struct Apply<0> {
    template<typename F, typename T, typename... A>
    static inline auto apply(F && f, T &&, A &&... a) {
        return ::std::forward<F>(f)(::std::forward<A>(a)...);
    }
};

template<typename F, typename T>
inline auto apply(F && f, T && t) {
    return Apply< ::std::tuple_size< typename ::std::decay<T>::type
      >::value>::apply(::std::forward<F>(f), ::std::forward<T>(t));
}

template<size_t I>
struct size_t_holder
{
    static const size_t value = I;
};

template<size_t Fn, size_t Vn, typename... Ts, typename R, typename... As>
auto set_value(std::tuple<Ts...> const& t, R& res, std::tuple<As...> const& a, size_t_holder<Vn>)
{
    std::cout << "Function = " << Fn << " " << "Variable = " << Vn << std::endl;
    res[Fn][Vn] = apply(get_jacobian_element<Fn, Vn>(t), a);
    return true;
}

template<typename... As>
void eat_up(As...){}

template<typename... Ts, size_t... Vs, size_t Fn, typename R, typename... As>
auto value_jacobian_at_internal(sz_seq<Vs...>, size_t_holder<Fn>, std::tuple<Ts...> const& t, R& res, std::tuple<As...> const& a)
{
    eat_up( set_value<Fn>(t,res,a,size_t_holder<Vs>())... );
    return true;
}

template<typename... Ts, size_t... Fs, typename R, typename... As>
auto value_jacobian_at(sz_seq<Fs...>, std::tuple<Ts...> const& t, R& res, std::tuple<As...> const& a)
{
    typedef typename std::tuple_element<0, std::tuple<Ts...>>::type type;
    eat_up( value_jacobian_at_internal(sz_gen_seq< std::tuple_size<type>::value >(), size_t_holder<Fs>(), t, res, a)... );
}

template<typename... Ts, typename R, typename... As>
auto value_jacobian_at(std::tuple<Ts...> const& t, R& res, As... as)
{
    value_jacobian_at(sz_gen_seq<sizeof...(Ts)>(), t, res, std::make_tuple(as...));    
}

template<typename... Ts>
constexpr size_t get_number_of_function(std::tuple<Ts...>)
{    
    typedef std::tuple<Ts...> type;
    return std::tuple_size<type>::value;
}

template<typename... Ts>
constexpr size_t get_number_of_variables(std::tuple<Ts...>)
{
    typedef typename std::tuple_element<0, std::tuple<Ts...>>::type type;
    return std::tuple_size< type >::value;
} 

#include <string>
#include <sstream>

namespace aks
{
    auto to_string( variable<0> v ){ return std::string("x"); }
    auto to_string( variable<1> v ){ return std::string("y"); }
    auto to_string( variable<2> v ){ return std::string("z"); }
    auto to_string( variable<3> v ){ return std::string("w"); }
    
    template<typename T> auto to_string( constant<T> c ){ std::stringstream ss; ss << c(); return ss.str(); }

    template<typename T, typename U> auto to_string( binary<T,U, add> b )
    { 
        auto t = to_string(b.t);
        auto u = to_string(b.u);
        
        if(t[0] > u[0]) { std::cout << "ADD swapping " << t << " and " << u << std::endl; std::swap(t,u); }
        
        if(t=="0" && u=="0")
            return std::string("0");        
        else if( t=="0" )
            {std::stringstream ss; ss << u; return ss.str(); }
        else if( u=="0" )
            {std::stringstream ss; ss << t; return ss.str(); }
        else if( t == u )
            { std::cout << "ADD " <<   t << " is the same as " << u << std::endl; std::stringstream ss; ss << "(2*" << t << ")"; return ss.str(); }
        else
            {std::stringstream ss; ss << "(" << t << "+" << u << ")"; return ss.str(); }
    }
    template<typename T, typename U> auto to_string( binary<T,U, sub> b )     
    { 
        auto  t = to_string(b.t);
        auto  u = to_string(b.u);
        
        if(t[0] > u[0]) { std::cout << "SUB swapping " << t << " and " << u << std::endl; std::swap(t,u); }
        
        if(t=="0" && u=="0")
            return std::string("0");        
        else if( t== u )
            { std::cout << "SUB " <<   t << " is the same as " << u << std::endl; return std::string("0"); }
        else if( t=="0" )
            {std::stringstream ss; ss << "(-" << u << ")"; return ss.str(); }
        else if( u=="0" )        
            {std::stringstream ss; ss << t; return ss.str(); }
        else
            {std::stringstream ss; ss << "(" << t << "-" << u << ")"; return ss.str(); }
    }
    
    template<typename T, typename U> auto to_string( binary<T,U, mul> b )
    {
        auto  t = to_string(b.t);
        auto  u = to_string(b.u);
        
        if(t[0] > u[0]) { std::cout << "MUL swapping " << t << " and " << u << std::endl; std::swap(t,u); }
        
        if(t=="0" || u=="0")
            return std::string("0");
        else if( t=="1" && u == "1" )
            return std::string("1");            
        else if( t=="1" )
            {std::stringstream ss; ss << u; return ss.str(); }
        else if( u=="1" )
            {std::stringstream ss; ss << t; return ss.str(); }
        else if(t == u )
            { std::cout << "MUL " <<  t << " is the same as " << u << std::endl; std::stringstream ss; ss << "(" << t << "^2)"; return ss.str(); }            
        else
            {std::stringstream ss; ss << "(" << t << "*" << u << ")"; return ss.str(); }
    }
    template<typename T, typename U> auto to_string( binary<T,U, dvd> b )
    {
        auto  t = to_string(b.t);
        auto  u = to_string(b.u);
        
        if(t[0] > u[0]) { std::cout << "DVD swapping " << t << " and " << u << std::endl; std::swap(t,u); }
        
        if(t == "0" && u == "0") 
            return std::string("(NaN)");
        else if(t=="0")
            return std::string("0");
        else if(u=="1")
            { std::stringstream ss; ss << t; return ss.str(); }
        else if(u=="0")
            return std::string("(Inf)");
        else if(t == u)
            { std::cout << "DVD " <<   t << " is the same as " << u << std::endl; return std::string("1"); }
        else
            {std::stringstream ss; ss << "("<< to_string(b.t) << "/" << to_string(b.u)<< ")"; return ss.str(); }
    }
    template<typename T, typename U> auto to_string( binary<T,U, mod> b ){ std::stringstream ss; ss << "("<< to_string(b.t) << "%" << to_string(b.u)<< ")"; return ss.str(); }
}
#include <algorithm>

template<typename T>
typename std::enable_if<T::dim == 1, double>::type newton_raphson( T f, double guess )
{
    double const d = 0.0001;
    auto df = aks::derivative(f);
    auto F = f/df;
    double delta = F(guess); 
    size_t count = 0;
    while(std::abs(delta) > 0.000001 && count++ < 20)
    {
        guess -= delta;
        delta = F(guess);
    }
    return guess;
}

int main()
{
    aks::variable<0> x;
    aks::variable<1> y;
    aks::variable<2> z;
    aks::variable<3> w;
    
    /*
    std::cout << ( (x)(2)       == 2 )    << std::endl;
    std::cout << ( (y)(2,3.5)   == 3.5 )  << std::endl;
    std::cout << ( (z)(2,3,4)   == 4 )    << std::endl;
    std::cout << ( (w)(2,3,4,5) == 5 )    << std::endl;
    
    std::cout << ( (x+x)(2)     == 4 )      << std::endl;
    std::cout << ( (y+y)(2,3.5) == 7.0 )    << std::endl;
    std::cout << ( (z+z)(2,3,4) == 8 )      << std::endl;
    
    std::cout << ( (x+x)(2)     == 4 )      << std::endl;
    std::cout << ( (x+y)(2,3.5) == 5.5 )    << std::endl;
    std::cout << ( (x+z)(2,3,4) == 6 )      << std::endl;    
    
    std::cout << ( (x+2)(2) == 4 ) << std::endl;
    std::cout << ( (2+x)(2) == 4 ) << std::endl;
    
    std::cout << ( ( x+y+3+z )(1,2,4) == 10 ) << std::endl;
    
    std::cout << ( (x*x)(2)     == 4 )      << std::endl;
    std::cout << ( (y*y)(2,3.5) == 12.25 )  << std::endl;
    std::cout << ( (z*z)(2,3,4) == 16 )     << std::endl;
    
    std::cout << ( (x*x)(2)     == 4 )      << std::endl;
    std::cout << ( (x*y)(2,3.5) == 7.0 )    << std::endl;
    std::cout << ( (x*z)(2,3,4) == 8 )      << std::endl;    
    
    std::cout << ( (x*2)(2) == 4 ) << std::endl;
    std::cout << ( (2*x)(2) == 4 ) << std::endl;
    
    std::cout << ( ( x*y*3*z )(1,2,4) == 24 ) << std::endl;
    
    std::cout << ( (x*y*z+x*x*x+y*z/(x*2.5)-z+z*z)(2.0,3.0,4.0) ) << std::endl;
    
    std::cout << ( ( x^5 )(2) == 32 ) << std::endl;
    std::cout << ( ( 5^x )(2) == 25 ) << std::endl;
    
    std::string const a("hello ");
    std::string const b("hello1 ");
    std::string const c("hello2 ");
    
    std::cout << (x+y+z)(a,b,c) << std::endl;
    std::cout << (cos(x))(3.14159265/3.0) << std::endl;
    std::cout << (atan2(x,y))(1.0, 2.0) << std::endl;
    
    std::cout << ( (sin(x)^2) + (cos(x)^2) )(0.23) << std::endl;
    
    std::cout << ( sin(x)/cos(x) )(0.23) << " " << (tan(x))(0.23) << std::endl;
    
    std::cout << sin(2*x)(0.23)  << " " << (2*sin(x)*cos(x))(0.23) << std::endl;   
    
    std::cout << sin(-x)(0.23)  << " " << (-sin(x))(0.23) << std::endl;
    
    std::cout << (exp(sin(x)^cos(y)*z)/w)(0.25, 0.50, 0.33, 0.75) << std::endl;
    
    std::cout << demangle(typeid((2*(x^y)+sqrt(w*z*x)*4.5/tan(x/y)*exp(sin(x)^cos(y)*z)/w)).name()) << std::endl;
    
    std::cout << get_dim(exp(sin(x)^cos(y)*z)) << std::endl;
    
    auto eq = (x*x-3.14159265);
    auto guess = 1.2;
    auto root = newton_raphson( eq , guess );
    std::cout << root << " " << eq(root) << std::endl;
    
    std::cout << depends_on(x*x, x) << std::endl;
    std::cout << depends_on(x*x, y) << std::endl;    
    std::cout << depends_on(x*y, y) << std::endl;
    std::cout << depends_on((2*x)^w+sqrt(w*x)*4.5/tan(x/w)*exp(sin(x)^cos(w)*z)/w, x) << std::endl;
    std::cout << depends_on((2*x)^w+sqrt(w*x)*4.5/tan(x/w)*exp(sin(x)^cos(w)*z)/w, y) << std::endl;
    std::cout << depends_on((2*x)^w+sqrt(w*x)*4.5/tan(x/w)*exp(sin(x)^cos(w)*z)/w, z) << std::endl;
    std::cout << depends_on((2*x)^w+sqrt(w*x)*4.5/tan(x/w)*exp(sin(x)^cos(w)*z)/w, w) << std::endl;
    auto dd = differentiate(x*y*y,y);
    std::cout << dd(2, 3) << std::endl;
    std::cout << demangle(typeid(dd).name()) << std::endl;   
    
    auto dd2 = differentiate(sin(y*x), x);
    std::cout << dd2(0.25, 0.63) << std::endl;
    
    std::cout << Max<3,2,4,2,5,3,6,3,2,4,2,2>::value << std::endl;
    
    */
    
    auto j = jacobian(x*w, y*z, y*y, z*z, x*x, y*x*z+x*w);
    std::vector<std::vector<double>> res(get_number_of_function(j), std::vector<double>(get_number_of_variables(j), 0.0));
            
    value_jacobian_at(j, res, 1.5, 3.3, 2.7, 3.4);
    
    std::for_each(res.cbegin(), res.cend(), []( std::vector<double> const& v ){
        std::for_each(v.cbegin(), v.cend(), []( double const& d ){
            std::cout << d << "\t";
        });
        std::cout << std::endl;
    });
    
    /*
    auto ds= x*y*z/x*x+2*x*y-y-x*x+x*y*z-3*x;
    auto dds = differentiate(ds,x);
    auto ddds = differentiate(dds,y);
    auto dddds = differentiate(ddds,z);
    auto ddddds = differentiate(dddds,x);
    
    std::cout << to_string(ds)    << "\n" 
              << to_string(dds)   << "\n" 
              << to_string(ddds)  << "\n" 
              << to_string(dddds) << "\n" 
              << to_string(ddddds)<< "\n" 
              << std::endl;
    
    std::cout << demangle(typeid(j).name()) << std::endl;
    std::cout << get_jacobian_element<0,0>(j)(1.5, 3.3, 2.7, 3.4) << ", ";
    std::cout << get_jacobian_element<0,1>(j)(1.5, 3.3, 2.7, 3.4) << ", ";
    std::cout << get_jacobian_element<0,2>(j)(1.5, 3.3, 2.7, 3.4) << std::endl;
    std::cout << get_jacobian_element<1,0>(j)(1.5, 3.3, 2.7, 3.4) << ", ";
    std::cout << get_jacobian_element<1,1>(j)(1.5, 3.3, 2.7, 3.4) << ", ";
    std::cout << get_jacobian_element<1,2>(j)(1.5, 3.3, 2.7, 3.4) << std::endl;
    std::cout << get_jacobian_element<2,0>(j)(1.5, 3.3, 2.7, 3.4) << ", ";
    std::cout << get_jacobian_element<2,1>(j)(1.5, 3.3, 2.7, 3.4) << ", ";
    std::cout << get_jacobian_element<2,2>(j)(1.5, 3.3, 2.7, 3.4) << std::endl;    
    std::cout << get_jacobian_element<3,0>(j)(1.5, 3.3, 2.7, 3.4) << ", ";
    std::cout << get_jacobian_element<3,1>(j)(1.5, 3.3, 2.7, 3.4) << ", ";
    std::cout << get_jacobian_element<3,2>(j)(1.5, 3.3, 2.7, 3.4) << std::endl;       
   
    auto fs_sum = x + y + z + (x^2.0) + x*y + x*z + (y^2.0) + y*z + (z^2.0) + (x^3.0);
    std::cout << "-------" << fs_sum(1.2, 3.2, 1.3) << "-------" << std::endl;
    
    auto fs = functions(x, y, z, x^2, x*y, x*z, y^2, y*z, z^2, x^3);
    auto eval = evaluate(fs, 1.2, 3.2, 1.3);
    
    std::cout << demangle(typeid(fs).name()) << std::endl;        
    std::cout << demangle(typeid(eval).name()) << std::endl;
    std::cout << demangle(typeid(fs_sum).name()) << std::endl;
    
    for_each_in_tuple(eval, []( double d ){ std::cout << d << ", "; }); std::cout << std::endl;
    double sum = 0;
    for_each_in_tuple(eval, [&sum]( double d ){ sum += d; });
    std::cout << "-------" << sum << "-------" << std::endl;
    
    std::cout << tan(sin(cos(x)))(0.23) << std::endl;
    
    auto g = x/3.0;
    auto dg = derivative(g);
    
    std::cout << demangle(typeid(g).name()) << std::endl;
    std::cout << demangle(typeid(dg).name()) << std::endl;
    std::cout << g(2.0) << " " << dg(2.0) << std::endl;
    
    auto h = sin(cos(x)*cos(x));
    auto dh = derivative(h);
    
    std::cout << demangle(typeid( h).name()) << std::endl;
    std::cout << demangle(typeid(dh).name()) << std::endl;
    std::cout << h(0.5) << " " << dh(0.5) << std::endl;    
    
    auto j2 = sqrt(x*x*x*x-2);
    auto dj2 = derivative(j2);
    
    std::cout << demangle(typeid( j2).name()) << std::endl;
    std::cout << demangle(typeid(dj2).name()) << std::endl;
    std::cout << j2(2) << " " << dj2(2) << std::endl;        
    
    auto k = exp(x*x);
    auto dk = derivative(k);
    
    std::cout << demangle(typeid( k).name()) << std::endl;
    std::cout << demangle(typeid(dk).name()) << std::endl;
    std::cout << k(2.0) << " " << dk(2.0) << std::endl;  

    auto m = cbrt(sin(x));
    auto dm = derivative(m);
    auto dm2 = derivative(dm);
    auto dm3 = derivative(dm2);
    auto dm4 = derivative(dm3);
    // auto dm5 = derivative(dm4);
    
    std::cout << demangle(typeid( m).name()) << std::endl;
    std::cout << demangle(typeid(dm).name()) << std::endl;
    std::cout << demangle(typeid(dm2).name()) << std::endl;
    std::cout << demangle(typeid(dm3).name()) << std::endl;
    std::cout << m(0.5) << " " << dm(0.5) << " " << dm2(0.5) << " " << dm3(0.5) << " " << dm4(0.5) << std::endl;  

    auto n   = -x*x;
    auto dn  = derivative(n);
    auto dn2 = derivative(dn);
    auto dn3 = derivative(dn2);
    auto dn4 = derivative(dn3);
    auto dn5 = derivative(dn4);
    
    std::cout << demangle(typeid( n).name()) << std::endl;
    std::cout << demangle(typeid(dn).name()) << std::endl;
    std::cout << demangle(typeid(dn2).name()) << std::endl;
    std::cout << demangle(typeid(dn3).name()) << std::endl;
    std::cout << n(0.5) << " " << dn(0.5) << " " << dn2(0.5) << " " << dn4(0.5);
 
    auto p   = x + x;
    auto dp  = aks::derivative(p);
    auto dp2 = aks::derivative(dp);
    auto dp3 = aks::derivative(dp2);
    
    std::cout << demangle(typeid( p).name()) << std::endl;
    std::cout << demangle(typeid(dp).name()) << std::endl;
    std::cout << demangle(typeid(dp2).name()) << std::endl;
    std::cout << demangle(typeid(dp3).name()) << std::endl;
    std::cout << p(0.5) << " " 
              << dp(0.5) << " " 
              << dp2(0.5) << " " 
              << dp3(0.5) << std::endl;   

    auto a0 = sin(x);
    auto a1  = differentiate(a0 , x);
    auto a2  = differentiate(a1 , x);
    auto a3  = differentiate(a2 , x);
    auto a4  = differentiate(a3 , x);
    auto a5  = differentiate(a4 , x);
    auto a6  = differentiate(a5 , x);
    auto a7  = differentiate(a6 , x);
    auto a8  = differentiate(a7 , x);
    auto a9  = differentiate(a8 , x);
    auto a10 = differentiate(a9 , x);
    auto a11 = differentiate(a10, x);
    //auto a12 = derivative(a11);
    
    std::cout << demangle(typeid(a0).name()) << std::endl;
    std::cout << demangle(typeid(a1).name()) << std::endl;
    std::cout << demangle(typeid(a2).name()) << std::endl;
    std::cout << demangle(typeid(a3).name()) << std::endl;
    std::cout << demangle(typeid(a4).name()) << std::endl;
    std::cout << demangle(typeid(a5).name()) << std::endl;
    std::cout << demangle(typeid(a6).name()) << std::endl;
    std::cout << demangle(typeid(a7).name()) << std::endl;
    std::cout << demangle(typeid(a8).name()) << std::endl;
    std::cout << demangle(typeid(a9).name()) << std::endl;
    std::cout << demangle(typeid(a10).name()) << std::endl;
    std::cout << demangle(typeid(a11).name()) << std::endl;
    //std::cout << demangle(typeid(a12).name()) << std::endl; 
    
    auto b0 = sqrt(x*y);
    auto b1 = differentiate(b0, y);
    std::cout << b0(20, 21) << " " << b1(20, 21) << std::endl;
    */

}