#include <string>
#include <sstream>
#include <iostream>
#include <typeinfo>
#include <vector>

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>

using boost::shared_ptr;
using boost::make_shared;
using boost::dynamic_pointer_cast;

struct Base {
    virtual ~Base() {}
    virtual shared_ptr<Base> clone() const = 0;
    virtual std::ostream& show(std::ostream&) const = 0;
protected:
    Base() {}
    Base(const Base&) {}
};

std::ostream& operator<<(std::ostream& o, const Base& b) {
    return b.show(o);
    }

struct A : Base {
    A() : Base() {}
    A(const A& a) : Base(a) {}
    virtual ~A() {}
    virtual std::ostream& show(std::ostream& o) const {
        o << "A";
        return o;
        }
    virtual shared_ptr<Base> clone() const {
        return make_shared<A>(*this);
        }
};

struct B : Base {
    B() : Base() {}
    B(const B& b) : Base(b) {}
    virtual ~B() {}
    virtual std::ostream& show(std::ostream& o) const {
        o << "B";
        return o;
        }
    virtual shared_ptr<Base> clone() const {
        return make_shared<B>(*this);
        }
};

typedef shared_ptr<Base> Base_ptr;
typedef shared_ptr<A> A_ptr;
typedef shared_ptr<B> B_ptr;

template<typename T>
void show(const std::string& name, const shared_ptr<T>& x) {
    std::cout << name << " item is " << *x << std::endl;
}

int main() {

    boost::uuids::random_generator gen_;

    std::stringstream ss;
    ss << gen_();
    std::string id_str_ = ss.str();

    std::cout << "run: " << id_str_ << std::endl;

    using std::vector;

    vector<shared_ptr<Base>> source {
        make_shared<A>()
        , make_shared<B>()
        , make_shared<A>()
        };

    for (const auto& item : source) {
        show("source", item);
        }

    vector<shared_ptr<Base>> cloned;

    for (auto& item : source) {
        cloned.push_back(item->clone());
        }

    for (auto& item : cloned) {
        show("cloned", item);
        }
}
