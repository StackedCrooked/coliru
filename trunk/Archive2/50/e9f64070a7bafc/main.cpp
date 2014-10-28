#ifndef CURRENCY_H
#define CURRENCY_H

//#include "Nameable.h"
#include <unordered_map>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/functional/hash.hpp>
//#include "BigDecimal.h"
#include <iostream>

struct Nameable {
    struct NameAlreadyTakenException : virtual std::exception {
        char const *what() const noexcept { return "NameAlreadyTakenException"; }
    };

    std::string name;
    virtual ~Nameable() = default;
};

/**
 * Represents a single currency. Can be used as keys in a map and as a general
 * identifier for determining what unit a value of money is.
 * @param name
 */
struct Currency : public Nameable {
    Currency(std::string name);
    Currency(const Currency &orig) = default;
    virtual ~Currency() = default;
    virtual std::string getName() const;
    virtual void setName(std::string name);
    inline bool operator==(const Currency &key) const { return id == key.id; }

    boost::uuids::uuid id;
};

// A template specialization for Currency.
namespace std {
template <> struct hash<Currency> {
    std::size_t operator()(const Currency &k) const {
        return boost::hash<boost::uuids::uuid>()(k.id);
    }
};
}
#endif /* CURRENCY_H */

Currency::Currency(std::string name)
    : id(boost::uuids::random_generator()())
{ 
    setName(name); 
}

std::string Currency::getName() const { 
    return this->name; 
}

void Currency::setName(std::string name) { 
    this->name = name;
}

int main() {
    Currency dollar("Dollar");
    std::unordered_map<Currency, int> currenMap;
    currenMap[dollar] = 1337;
    std::cout << currenMap[dollar] << "\n";
}
