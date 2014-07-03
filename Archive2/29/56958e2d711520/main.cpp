#include <iostream>
#include <string>
#include <future>
#include <thread>
#include <utility>
#include <functional>
#include <type_traits>
#include <boost/fusion/container/vector.hpp>
#include <boost/optional.hpp>

template<typename T>
class Generator {
public:
    class Iterator {
    public:
        T operator*() {
            if (!value) {
                throw "Bena vagy.";
            }
            
            return *value;
        }
        
        Iterator& operator++() {
            value = functor();
            return *this;
        }
        
        bool operator==(const Iterator& other) {
            return !value && !other.value; //FIXME: this only works for end()
        }
        
        bool operator!=(const Iterator& other) {
            return !operator==(other);
        }
    private:
        Iterator() {
        }
    
        Iterator(std::function<boost::optional<T>()> functor) : functor{functor}, value{this->functor()} {
        }
        
        std::function<boost::optional<T>()> functor;
        boost::optional<T> value; //TODO: lazy evaluation
        
        friend Generator;
    };

    Generator(std::function<boost::optional<T>()> functor) : functor{functor} {
    }
    
    Iterator begin() {
        return {functor};
    }
    
    Iterator begin() const {
        return {functor};
    }
    
    Iterator end() const {
        return {};
    }

private:
    std::function<boost::optional<T>()> functor;
};

Generator<int> getPositiveNumbers() {
    int n = 0;
    return {[=]() mutable -> boost::optional<int> { // "()" required before "mutable"
                return ++n;
            }};
}

template<typename Iterable>
auto limitSequence(Iterable generator, int limit) -> Generator<decltype(*std::begin(std::declval<Iterable>()))> {
    auto iterator = std::begin(generator);
    auto end = std::end(generator);
    using Optional = boost::optional<decltype(*std::begin(std::declval<Iterable>()))>;
    
    return {[=]() mutable -> Optional { // "()" required before "mutable"
                auto number = *iterator;
                ++iterator;
                
                if (iterator == end) {
                        return boost::none;
                }
                
                return number < limit ? Optional{number} : Optional{};
            }};
}

template<typename Iterable>
auto selectEvenNumbers(Iterable generator) -> Generator<decltype(*std::begin(std::declval<Iterable>()))> {
    auto iterator = std::begin(generator);
    auto end = std::end(generator);
    using Optional = boost::optional<decltype(*std::begin(std::declval<Iterable>()))>;
    
    return {[=]() mutable -> Optional {
                while (iterator != end) {
                    auto number = *iterator;
                    ++iterator;
                    
                    if (number % 2 == 0) {
                        return number;
                    }
                }
                
                return boost::none;
            }};
}

int main() {
    auto positiveNumbers = getPositiveNumbers();
    auto evenPositiveNumbers = selectEvenNumbers(positiveNumbers);
    auto limitedEven = limitSequence(evenPositiveNumbers, 9);

    for (auto number : limitedEven) {
        std::cout << number << std::endl;
    }
    
    return 0;
}