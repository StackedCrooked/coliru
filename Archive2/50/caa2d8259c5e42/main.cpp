#include <iostream>
#include <string>
#include <vector>
#undef min
#undef max
#include <algorithm>
#include <boost/thread.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/range/algorithm_ext/insert.hpp>
#include <boost/range/adaptors.hpp>
#include <boost/range/adaptor/filtered.hpp>
#include <boost/range/algorithm_ext/erase.hpp>
#include <boost/range/algorithm_ext/push_back.hpp>
#include <boost/range/numeric.hpp>
#include <boost/range/adaptor/indexed.hpp>
#include <boost/algorithm/clamp.hpp>

void Dummy(){
/*
      // Scala version
      case class Person(name:String, age:Int);
      val guys = Person("Joe", 24) :: Person("Mike", 33) :: Person("Duke", 16) :: Nil
      val max_age = guys.map{_.age}.max
      val max_aged_person = guys.maxBy{_.age}
      val max_age2 = guys.foldLeft(-1){_ max _.age}   
*/
    struct Person{
        Person(std::string const& name_, int age_):name(name_),age(age_){};
        std::string name;
        int age;
    };

    std::vector<Person> guys;
    guys.emplace_back("Joe", 24);
    guys.emplace_back("Mike", 33);
    guys.emplace_back("Duke", 16);

    {
        int max_age(-1);
        for(int i=0; i<guys.size(); ++i)
            max_age = std::max<int>(max_age, guys[i].age);
    }
    {
        int max_age(-1);
        for(auto &p : guys)
            max_age = std::max<int>(max_age, p.age);
    }
    {
        int max_age = -1;
        std::for_each(guys.begin(), guys.end(),
            [&max_age](Person &p){max_age = std::max<int>(max_age, p.age);});
    }
    {
        const int max_age = std::max_element(guys.begin(), guys.end(),
            [](Person &p0, Person &p1){return p0.age < p1.age;})
            ->age;
    }
    {
        const auto it = std::max_element(guys.begin(), guys.end(),
            [](Person &p0, Person &p1){return p0.age < p1.age;});
        const int max_age = it!=guys.end() ? it->age: -1;
    }
    {
        std::vector<int> age_vec;
        std::transform(guys.begin(), guys.end(), std::back_inserter(age_vec),
            [](Person v){return v.age;});
        const int max_age = *std::max_element(age_vec.begin(), age_vec.end());
    }
    {
        const int max_age = std::accumulate(guys.begin(), guys.end(), -1,
            [](int max_phase, Person &p){ return std::max<int>(max_phase, p.age); });
    }
    {
        const int max_age = [&guys]{
            int max_age(-1);
            for(auto &i : guys)
                max_age = std::max<int>(max_age, i.age);
            return max_age;
        }();
    }
    {
        const int max_age(-1);
        for(auto &i : guys)
            *const_cast<int*>(&max_age) = std::max<int>(max_age, i.age);
    }
    {
        const int max_age = boost::max_element(guys,
            [](Person &p0, Person &p1){return p0.age < p1.age;})->age;
    }
    {
        const int max_id = *boost::max_element(guys | boost::adaptors::transformed(
            std::function<int(Person)>([](Person const &p){return p.age;})));
    {
    }
        const int max_id2 = boost::accumulate(guys, -1, 
            [](int l, Person const &r){return std::max(l, r.age);});
    }
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}
int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
}
