#include <iostream>
#include <vector>
 
const static auto null = nullptr;
 
template<typename TFuncSignature>
class Callback;
 
template<typename R, typename A1>
class Callback<R (A1)> {
public:
    typedef R (*TFunc)(void*, A1);
 
        Callback() : obj(0), func(0) {}
        Callback(void* o, TFunc f) : obj(o), func(f) {}
 
        R operator()(A1 a1) const {
                return (*func)(obj, a1);
        }
 
        typedef void* Callback::*SafeBoolType;
        operator SafeBoolType () const {
                return func != 0? &Callback::obj : 0;
        }
 
        bool operator! () const {
                return func == 0;
        }
 
        bool operator== ( const Callback<R (A1)>& right ) const {
                return obj == right.obj && func == right.func;
        }
 
        bool operator!= ( const Callback<R (A1)>& right ) const {
                return obj != right.obj || func != right.func;
        }
 
private:
        void* obj;
        TFunc func;
};
 
template<typename R, class T, typename A1>
struct DeduceMemCallbackTag {
        template<R (T::*Func)(A1)>
        static R Wrapper(void* o, A1 a1) {
                return (static_cast<T*>(o)->*Func)(a1);
        }
 
        template<R (T::*Func)(A1)>
        inline static Callback<R (A1)> Bind(T* o) {
                return Callback<R (A1)>(o, &DeduceMemCallbackTag::Wrapper<Func>);
        }
};
 
template<typename R, typename A1>
struct DeduceStaticCallbackTag {
        template<R (*Func)(A1)>
        static R Wrapper(void*, A1 a1) {
                return (*Func)(a1);
        }
 
        template<R (*Func)(A1)>
        inline static Callback<R (A1)> Bind( ) {
                return Callback<R (A1)>( 0, &DeduceStaticCallbackTag::Wrapper<Func> );
        }
};
 
template<typename R, class T, typename A1>
DeduceMemCallbackTag<R, T, A1> DeduceMemCallback(R (T::*)(A1)) {
        return DeduceMemCallbackTag<R, T, A1>();
}
 
template<typename R, typename A1>
DeduceStaticCallbackTag<R, A1> DeduceStaticCallback(R (*)(A1)) {
        return DeduceStaticCallbackTag<R, A1>();
}
 
template <typename T1> class Event {
public:
        typedef void(* TSignature)( T1 );
        typedef Callback<void( T1 )> TCallback;
 
protected:
        std::vector<TCallback> invocations;
        std::vector<Event<T1>*> events;
 
public:
        const static int ExpectedFunctorCount = 2;
 
        Event () : invocations(), events() {
                invocations.reserve( ExpectedFunctorCount );
                events.reserve( ExpectedFunctorCount );
        }
 
        template <void (* TFunc)(T1)> void Add (  ) {
                TCallback c = DeduceStaticCallback( TFunc ).template Bind< TFunc >( );
                invocations.push_back( c );
        }
 
        template <typename T, void (T::* TFunc)(T1)> void Add ( T& object ) {
                Add<T, TFunc>( &object );
        }
 
        template <typename T, void (T::* TFunc)(T1)> void Add ( T* object ) {
                TCallback c = DeduceMemCallback( TFunc ).template Bind< TFunc >( object );
                invocations.push_back( c );
        }
 
        void Invoke ( T1 t1 ) {
                size_t i;
                for ( i = 0; i < invocations.size(); ++i ) {
                        invocations[i]( t1 );
                }
                for ( i = 0; i < events.size(); ++i ) {
                        (*events[i])( t1 );
                }
        }
 
        void operator() ( T1 t1 ) {
                Invoke( t1 );
        }
 
        size_t InvocationCount ( ) {
                return events.size( ) + invocations.size( );
        }
 
        template <void (* TFunc)(T1)> bool Remove ( ) {
                TCallback target = DeduceStaticCallback( TFunc ).template Bind< TFunc >( );
                for ( size_t i = 0; i < invocations.size(); ++i ) {
                        TCallback& inv = invocations[i];
                        if ( target == inv ) {
                                invocations.erase( invocations.begin() + i );
                                return true;
                        }
                }
                return false;
        }
 
        template <typename T, void (T::* TFunc)(T1)> bool Remove ( T& object ) {
                return Remove<T, TFunc>( &object );
        }
 
        template <typename T, void (T::* TFunc)(T1)> bool Remove ( T* object ) {
                TCallback target = DeduceMemCallback( TFunc ).template Bind< TFunc >( object );
                for ( size_t i = 0; i < invocations.size(); ++i ) {
                        TCallback& inv = invocations[i];
                        if ( target == inv ) {
                                invocations.erase( invocations.begin() + i );
                                return true;
                        }
                }
                return false;
        }
 
};
 
namespace IntStatic {
    void VoidTest    ()         { std::cout << "INTO THE VOID"         << std::endl; }
    void IntTest     (int num)  { std::cout << "Got myself a "         << num  << " !"    << std::endl; }
    void IntTest2    (int num)  { std::cout << "Now _I_ Got myself a " << num  << " !"    << std::endl; }
}
struct Int {
    void Test        (int num)  { std::cout << num  << " on the inside of a class... ?"   << std::endl; }
    void Test2       (int num)  { std::cout << num  << " on the inside of a struct, yo !" << std::endl; }
    static void Test3(int snum) { std::cout << snum << " on the inside of a class... ?"   << std::endl; }
};
 
int main() {
    Event<int> intev;
    Int i;
    intev.Add<Int, &Int::Test>(i);
    intev.Add<&IntStatic::IntTest>();
    intev.Add<&IntStatic::IntTest2>();
    //intev.Add( Int::Test3 );
    intev(20);
    intev.Remove<&IntStatic::IntTest>();
    intev.Remove<&IntStatic::IntTest>();
    intev.Remove<Int, &Int::Test>(i);
    //intev.Remove( Int::Test3 );
    //intev.Remove( i, &Int::Test );
    intev(20);
    return 0;
}
