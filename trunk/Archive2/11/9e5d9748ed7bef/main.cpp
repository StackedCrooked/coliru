#include <boost/tuple/tuple.hpp>
#include <boost/variant.hpp>
#include <boost/fusion/adapted/boost_tuple.hpp>
#include <boost/fusion/algorithm/iteration/for_each.hpp>
#include <iostream>

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
        Flusher<AnimatedStateType> flusher;
        boost::fusion::for_each(renderStates_, flusher);
        auto& states = boost::get<std::vector<AnimatedStateType>>(renderStates_);
        states.push_back(state);
    }

/*
    void flush()
    {
        boost::fusion::for_each(renderStates_, Flusher<void>());
    }
*/    

private:
    /**
     * Flashes all the vectors except vector of CurrenrStateType
     */
    template <typename CurrenrStateType>
    struct Flusher {
        void operator()(std::vector<CurrenrStateType>&) const {}

        template <typename StateType>
        void operator()(std::vector<StateType>&) const 
        {
            flush(boost::get<std::vector<StateType>>(renderStates_));
        }
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
    }

    boost::tuple<std::vector<RenderStateTypes>...> renderStates_;
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
    return 0;
}    

