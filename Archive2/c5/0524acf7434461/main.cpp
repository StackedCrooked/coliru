#include <vector>
#include <map>
#include <boost/weak_ptr.hpp>
#include <boost/make_shared.hpp>
#include <iostream>

using std::string;
using boost::shared_ptr;
using boost::weak_ptr;
using boost::make_shared;

struct Person {
    string name_;
    Person(string name) : name_(move(name)) {}

    using tag = weak_ptr<void>;
    
    tag track() const { return tracking_tag; }

  private:
    shared_ptr<void> tracking_tag = make_shared<char>('x');
};

template <typename T>
inline bool IsDeleted(weak_ptr<T> const& v) {
    return !v.lock();
}

enum favcolor { red, blue, pink, magenta, beige } favorite_color;

template <typename Map> size_t garbage_collect(Map& map)
{
    size_t collected = 0;
    for (auto it = map.begin(); it!=map.end();)
    {
        if (IsDeleted(it->first))
            ++collected, it = map.erase(it);
        else
            ++it;
    }

    return collected;
}

int main()
{
    std::vector<Person> people;

    for (auto&& name : { "John", "Mike", "Garbarek", "Milou", "Confucius", "Kiplat" })
        people.emplace_back(name);

    struct Properties {
        favcolor favorite_color;
        struct Car { string brand; int year; } vehicle;
    };

    std::map<Person::tag, Properties> associated {
        { people[0].track(), Properties { magenta, { "Chevy", 1986 } } },
        { people[2].track(), Properties { pink,    { "Kia",   2011 } } },
    };

    for (auto& p : people) std::cout << p.name_ << " "; std::cout << "\n";
    std::cout << "Defined properties: " << associated.size() << "\n";

    people.erase(std::remove_if(people.begin(), people.end(), [](Person const& p) { return p.name_[1] == 'o'; }), people.end());

    for (auto& p : people) std::cout << p.name_ << " "; std::cout << "\n";
    std::cout << "Defined properties before garbage collect: " << associated.size() << "\n";

    auto count = garbage_collect(associated);
    std::cout << "Defined properties after garbage collect: " << associated.size() << " (" << count << " collected)\n";
}


