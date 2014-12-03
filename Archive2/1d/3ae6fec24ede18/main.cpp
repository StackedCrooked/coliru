#include <boost/variant.hpp>
#include <memory>
#include <iostream>

namespace nature_detail {
    template <typename> struct Nature;
    template<> struct Nature<struct FooTag> { void do_it() { std::cout << "Foo" << "\n"; } };
    template<> struct Nature<struct BarTag> { void do_it() { std::cout << "Bar" << "\n"; } };

    using FooNature = Nature<FooTag>;
    using BarNature = Nature<BarTag>;

    using AnyNature = boost::variant<FooNature, BarNature>;

    struct Holder {
        AnyNature held;
        ~Holder() { DoIt()(held); }

      private:
        struct DoIt : boost::static_visitor<> {
            void operator()(AnyNature& any)                  const { return boost::apply_visitor(*this, any); }
            template <typename N> void operator()(N& nature) const { return nature.do_it(); }
        };
    };

}

#include <vector>

int main(void) {
    using InterfaceWrapper = std::shared_ptr<nature_detail::Holder>;
    using Thing = InterfaceWrapper::element_type;

    {
        std::vector<InterfaceWrapper> thing_vector;

        auto thing = std::make_shared<Thing>();

        thing_vector.push_back(thing);
        thing_vector.push_back(thing);
        thing_vector.push_back(thing);
        thing_vector.push_back(thing);
    } // prints "Foo" once

    {
        std::vector<InterfaceWrapper> thing_vector;

        auto thing = std::make_shared<Thing>();

        thing_vector.push_back(thing);
        thing_vector.push_back(thing);
        thing_vector.push_back(thing);

        thing->held = nature_detail::BarNature {}; // prints nothing

        thing_vector.push_back(thing);
    } // prints "Bar" once
}
