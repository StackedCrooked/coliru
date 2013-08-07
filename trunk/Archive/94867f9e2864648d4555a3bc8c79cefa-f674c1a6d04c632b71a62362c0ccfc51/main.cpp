#include <iostream>
#include <string>
#include <vector>


class Base { public: virtual int Do(){return 0;} };
class State1: public Base {};
class State2: public Base {};

template <typename ... T> class SM;

template <class StateBase, class HeadState, class ... States >
class SM<StateBase, HeadState, States...> : public SM< StateBase, States...>
{
    protected:
        HeadState headState;
        template<int cnt> StateBase* GetNextState ( unsigned int index ) { return headState; }
};  

template <class StateBase, class HeadState>
class SM< StateBase, HeadState>
{
    protected:
        HeadState headState;
        template<int cnt> StateBase* GetNextState ( unsigned int index ) { return headState; }
};  

template <class StateBase, class ... States >
class TopSM: public SM< StateBase, States...>
{
    public:
        void DoIt()
        {
            // following code fails with 
            // error: invalid operands of types '<unresolved overloaded function type>' and 'int' to binary 'operator<'
            int nextState = this->template SM< StateBase, States...>::GetNextState <1>( 1 );
        }
};  

TopSM<Base, State1, State2> sm;

int main()
{
    sm.DoIt();
    return 0;
}

