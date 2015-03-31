#include <tuple>
#include <type_traits>
#include <boost/operators.hpp>

#include <iostream>
#include <string>

template <typename Names, class ... Types>
class NamedTuple : public boost::operators<NamedTuple<Names, Types...>> {
    static constexpr typename std::underlying_type<Names>::type toUIType(Names enumerator) noexcept {
        return static_cast<typename std::underlying_type<Names>::type>(enumerator);
    }
    
    public:
    template<Names name>
    decltype(std::get<toUIType(name)>(std::tuple<Types...>{}))& get(){
        return std::get<toUIType(name)>(data);
    }
    
    template<Names name>
    const decltype(std::get<toUIType(name)>(std::tuple<Types...>{}))& get() const {
        return std::get<toUIType(name)>(data);
    }
    
    bool operator==(const NamedTuple& rhs) const {
        return data == rhs.data;
    }
    
    bool operator<(const NamedTuple& rhs) const {
        return data < rhs.data;
    }
    
    private:
    std::tuple<Types...> data;
};

int main(int argc, char* argv[])
{
    enum class Fields{Name, Age};
    NamedTuple<Fields, std::string, unsigned int> person;
    
    person.get<Fields::Name>() = "Stefano Falasca";
    person.get<Fields::Age>() = 29;
    
    std::cout << person.get<Fields::Name>() << ": " << person.get<Fields::Age>() << std::endl;
    
    if(person != person){
        std::cout << "the impossible happened" << std::endl;
    }
    if(person > person){
        std::cout << "the impossible happened" << std::endl;
    }
}
