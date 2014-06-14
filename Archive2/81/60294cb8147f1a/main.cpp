#include <boost/phoenix.hpp>
#include <boost/phoenix/stl.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/proto/functional/std.hpp>
#include <vector>
#include <map>

namespace phx = boost::phoenix;
using namespace phx::arg_names;

struct Person {
    std::string _name;
    int         _age;

    Person(std::string name, int age) : _name(name), _age(age) {}

    std::string getName() const { return _name; }
    int         getAge()  const { return _age;  }
};

int ageRank(int age) {
    static int const AGE_LOW_LEVEL  = 10;
    static int const AGE_HIGH_LEVEL = 60;

    if (age < AGE_LOW_LEVEL)  return age + 2; 
    if (age < AGE_HIGH_LEVEL) return age + 1;   

    return age - 5;
}

int ageRank(Person const& person) {
    return ageRank(person.getAge());
}

BOOST_PHOENIX_ADAPT_FUNCTION(int, ageRank_, ageRank, 1)
phx::function<boost::proto::functional::make_pair> make_pair_;

int main() {
    std::vector<Person> vec;
    vec.push_back(Person("John",   12));
    vec.push_back(Person("Sara",   2));
    vec.push_back(Person("Chang",  73));
    vec.push_back(Person("Mbekip", 24));

    typedef std::map<std::string, int> RankMap;
    RankMap result;

    boost::transform(
            vec, 
            std::inserter(result, result.end()), 
            make_pair_(phx::bind(&Person::getName, arg1), ageRank_(arg1))
        );

    for(RankMap::const_iterator it=result.begin(); it!=result.end(); ++it)
    {
        std::cout << it->first << " -> " << it->second << "\n";
    }
}
