#include <boost/tuple/tuple.hpp>
#include <boost/variant.hpp>
#include <boost/fusion/adapted/std_tuple.hpp>
#include <boost/fusion/algorithm/iteration/for_each.hpp>
#include <iostream>

//remove after switch on C++14
namespace std {
template<typename T, typename... Ts>
struct Index {};

template<typename T, typename T1, typename... Ts>
struct Index<T, T1, Ts...> {
    static const size_t value = 1 + Index<T, Ts...>::value;
};

template<typename T, typename... Ts>
struct Index<T, T, Ts...> {
    static const size_t value = 0;
};

template <typename T, typename... Pack>
T& get(std::tuple<Pack...>& tuple)
{
    return std::get<Index<T, Pack...>::value>(tuple);
}
} //std

/*
int main() {
    std::cout << Index<std::vector<int>, double, int, std::vector<int>, std::set<float>, bool>::value;
    return 0;
}*/

/*
template <typename T>
struct Getter {
    void operator()(T& item) const {}
    
    T& fiund
};

template <typename T, typename TupleType>
T& get(TupleType& typle)
{
    
}*/    


template<typename... T>
class MultiCollection {
public:
    void add(const boost::variant<T...>& item) { collection_.push_back(item); }

    void add(MultiCollection<T...>&& other)
    {
        std::move(other.collection_.begin(), other.collection_.end(),
                std::back_inserter(collection_));
    }

    template <typename ComparatorType>
    void sort(const ComparatorType& cmp) {
        std::sort(collection_.begin(), collection_.end(), cmp);
    }

    template <typename Visitor>
    void traverse(Visitor& visitor) {
        for (auto& item : collection_) {
            boost::apply_visitor(visitor, item);
        }
    }

private:
    std::vector<boost::variant<T...>> collection_;
};

template<typename... RenderStateTypes>
class RenderVisitor : public boost::static_visitor<> {
public:
    template <typename AnimatedStateType>
    void operator()(AnimatedStateType& state)
    {
        boost::fusion::for_each(renderStates_, Flusher<AnimatedStateType>(this));
        auto& states = std::get<std::vector<AnimatedStateType>>(renderStates_);
        states.push_back(state);
    }
    
    void flush() 
    {
        boost::fusion::for_each(renderStates_, Flusher<void>(this));
    }    

private:
    /**
     * Flashes all the vectors except vector of CurrentStateType
     */
    template <typename CurrentStateType>
    struct Flusher {
        Flusher(RenderVisitor* visitor) : visitor(visitor) {}
        
        void operator()(std::vector<CurrentStateType>&) const {}

        template <typename StateType>
        void operator()(std::vector<StateType>&) const 
        {
            visitor->flush(std::get<std::vector<StateType>>(visitor->renderStates_));
        }
        
        RenderVisitor* visitor;
    };

    template <typename AnimatedStateType>
    void flush(std::vector<AnimatedStateType>& states)
    {
        if (states.empty()) {
            return;
        }
        
        for (auto& state : states) {
            state.flush();
        }
        states.clear();
    }

    std::tuple<std::vector<RenderStateTypes>...> renderStates_;
};

struct A {
    void flush() { std::cout << "flush()[A]" << "\n"; }
};

struct B {
    void flush() { std::cout << "flush()[B]" << "\n"; }
};

int main(void) {
    MultiCollection<A, B> collection;
    collection.add(A());
    collection.add(A());
    collection.add(B());
    
    RenderVisitor<A, B> v;
    collection.traverse(v);
    v.flush();
    return 0;
}    

