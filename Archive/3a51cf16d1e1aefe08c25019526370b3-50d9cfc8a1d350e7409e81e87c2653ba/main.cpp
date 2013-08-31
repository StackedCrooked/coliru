#include <thread>
#include <vector>
#include <atomic>
#include <memory>
#include <iostream>

template<unsigned...> struct indices{};

template<unsigned N, unsigned... Is>
struct indices_gen : indices_gen<N-1, N-1, Is...>{};

template<unsigned... Is>
struct indices_gen<0, Is...> : indices<Is...>{};

class Thread {
private:
    struct ThreadJumpBase {
        virtual void operator() () const { std::cout << "Thread Base" << std::endl; };
        virtual ~ThreadJumpBase () {};
    };
    
    template <typename R, typename ...T>
    struct ThreadJump : public ThreadJumpBase {
        std::function<R( T... )> fx;
        std::tuple<T...> args;
        
        template <typename Fx, typename ...Tx>
        ThreadJump ( Fx&& f, Tx&&... params ) : fx( f ), args( std::forward<Tx>( params )... ) {
            
        }
        
        virtual void operator () () const override {
            Invoke( indices_gen<sizeof...(T)>() );
        }
        
        template <unsigned ... I>
        void Invoke ( indices<I...> ) const {
            fx( std::move( std::get<I>( args ) )... );
        }
    };
    
    std::unique_ptr<ThreadJumpBase> threadjump;
    std::atomic<bool> done;
    std::thread thread;
    
public:

    template <typename Fx, typename ...T>
    Thread ( Fx&& fx, T&&... args ) : 
    threadjump( new ThreadJump<void, T...>( fx, std::forward<T>( args )... ) ), 
    done( false ), 
    thread( [&](){ (*threadjump)(); } ) {
    
    }
    
    bool Done () const {
        return done;
    }
    
    void Join () {
        thread.join();
    }
};

void abc ( int val ) {
    std::cout << val << std::endl;
}

int main () {
    Thread t(&abc, 1);
    t.Join();
    std::cout << 2 << std::endl;
}
