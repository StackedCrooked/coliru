
struct __nat
{
    ~__nat() = delete;
};

template <class ..._Args>
auto
__invoke(_Args&& ...__args)
    -> __nat;

template <class _Fp, class ..._Args>
auto
__invoke(_Fp&& __f, _Args&& ...__args)
    -> decltype(__f(__args...));

template <class _Tp> class  tuple_element;

template <class _Tp> class  tuple;
template <class _Tp>
typename tuple_element<tuple<_Tp> >::type&
get(tuple<_Tp>&) ;

template <class ..._Tp> struct __tuple_types {};

template <class _Hp, class ..._Tp>
class  tuple_element<__tuple_types<_Hp, _Tp...> >
{
public:
    typedef _Hp type;
};

template <class ..._Tp>
class  tuple_element<tuple<_Tp...> >
{
public:
    typedef typename tuple_element<__tuple_types<_Tp...> >::type type;
};

template <class _Tp>
class  tuple
{
};

template <class _Fp>
class __call_once_param
{
    _Fp __f_;
public:
    void operator()()
    {
        __invoke(get(__f_));
    }
};

template <class _Fp>
void
__call_once_proxy(void* __vp)
{
    __call_once_param<_Fp>* __p = static_cast<__call_once_param<_Fp>*>(__vp);
    (*__p)();
}

void __call_once(void(*)(void*));

template<class _Callable>
void
call_once(_Callable&& __func)
{
        __call_once(&__call_once_proxy<tuple<_Callable>>);
}

void foo(void) {}

int
main()
{
    call_once(&foo);
    return 1;
}
