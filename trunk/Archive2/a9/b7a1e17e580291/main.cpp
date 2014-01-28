#include <iostream>
#include <type_traits>

template <typename T>
using RemoveReference = typename std::remove_reference<T>::type;

template <typename T>
using RemoveCv = typename std::remove_cv<T>::type;

template <bool T, typename U = void>
using DisableIf = typename std::enable_if<!T, U>::type;

template <typename T>
using Bare = RemoveCv<RemoveReference<T>>;

template <typename T, typename... U>
struct is_related : std::false_type {};

template <typename T, typename U>
struct is_related<T, U> : std::is_same<Bare<T>, Bare<U>> {};

template<class Obj>
class wrapper {
protected:
    Obj _Data;
public:

    wrapper(const wrapper<Obj>& w): _Data(w._Data) {}

        template <typename... Args,
                  DisableIf<is_related<wrapper<Obj>, Args...>::value>...>
        wrapper(Args&&... args):
            _Data(std::forward<Args>(args)...) {}

    inline Obj& operator()() { return _Data; }

    virtual ~wrapper() {}
};

int main()
{
    wrapper<int> w1(9);
    wrapper<int> w2(w1);
}
