#include <boost/serialization/serialization.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <iostream>
#include <sstream>

using namespace boost;

class Person {
  public:
    Person(int a = 0) : age(a) {}
    bool operator==(const Person &rhs) const { return age == rhs.age; }

  private:
    int age;

    friend class boost::serialization::access;
    template <typename Archive> void serialize(Archive &a, unsigned int) { a &age; }
};

Person** make_persons(size_t n) {
    Person **persons = new Person *[n];
    int i = 10;
    std::generate_n(persons, n, [i]{ return new Person(i); });

    return persons;
}

void free_persons(Person** persons, size_t n) {
    std::for_each(persons, persons+n, [](Person*p){ delete p; });
    delete[] persons;
}

int main() {
    const size_t n = 10;
    Person** persons = make_persons(n);

    std::stringstream ss;

    archive::binary_oarchive oa(ss);
    oa << n << serialization::make_array(persons, n);

    archive::binary_iarchive ia(ss);
    size_t loaded_size;
    ia >> loaded_size;
    Person** loaded = new Person*[loaded_size];
    ia >> serialization::make_array(loaded, loaded_size);

    assert(n == loaded_size);
    for (size_t i = 0; i < n; ++i)
        assert(*persons[i] == *loaded[i]);

    free_persons(loaded, n);
    free_persons(persons, n);
}
