#include <boost/msm/msm_grammar.hpp>
#include <boost/msm/front/state_machine_def.hpp>
#include <boost/msm/back/state_machine.hpp>
#include <iostream>

struct E {
};

struct A : public boost::msm::front::state<> {
    template <class IE, class SM> void on_entry(IE const&, SM&) { std::cout << __PRETTY_FUNCTION__ << "\n"; } 
    template <class SM> void on_entry(E const&, SM&)            { std::cout << __PRETTY_FUNCTION__ << "\n"; } 
    template <class IE, class SM> void on_exit (IE const&, SM&) { std::cout << __PRETTY_FUNCTION__ << "\n"; } 
};

struct B : public boost::msm::front::state<> {
    template <class IE, class SM> void on_entry(IE const&, SM&) { std::cout << __PRETTY_FUNCTION__ << "\n"; } 
    template <class IE, class SM> void on_exit (IE const&, SM&) { std::cout << __PRETTY_FUNCTION__ << "\n"; } 
};

struct SubMachineDefinition : public boost::msm::front::state_machine_def<SubMachineDefinition>
{
    typedef boost::msm::front::state_machine_def<SubMachineDefinition> Base;

    typedef A initial_state;

    struct transition_table : boost::mpl::vector<
        typename Base::template _row<A, E, B>,
        typename Base::template _row<B, E, A>
    > {};

    template <class IE, class SM> void on_entry(IE const&, SM&) { std::cout << __PRETTY_FUNCTION__ << "\n"; } 
    template <class IE, class SM> void on_exit (IE const&, SM&) { std::cout << __PRETTY_FUNCTION__ << "\n"; } 
};

struct SuperMachineDefinition : public boost::msm::front::state_machine_def<SuperMachineDefinition > {
    typedef boost::msm::back::state_machine<SubMachineDefinition> SubMachine;
    typedef SubMachine initial_state;
    
    struct transition_table : boost::mpl::vector<> {};
};

int main() {
    boost::msm::back::state_machine<SuperMachineDefinition> states;
    states.start();
    states.process_event(E());
    states.process_event(E());
    states.process_event(E());
    states.process_event(E());
    states.process_event(E());
}
