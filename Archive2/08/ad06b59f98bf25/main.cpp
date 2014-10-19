#include <iostream>
#include <memory>
#include <string>

namespace detail {

template <class T>
class Holder {
  public:
    using Data = T;

    Holder(T obj) : data_(std::move(obj)) {}
    virtual ~Holder() = default;
    T &get() { return data_; }
    const T &get() const { return data_; }

  private:
    T data_;
};

template <class Concept_, template <class> class Model>
class Container {
  public:
    using Concept = Concept_;

    template <class T>
    Container(T obj)
        : self_(std::make_shared<Model<Holder<T>>>(std::move(obj))) {}

    const Concept &get() const { return *self_.get(); }

  private:
    std::shared_ptr<const Concept> self_;
};

// Helpers for spec merging.
template <class Spec>
using ConceptOf = typename Spec::Concept;
template <class Spec, class Holder>
using ModelOf = typename Spec::template Model<Holder>;
template <class Spec, class Container>
using ExternalInterfaceOf =
    typename Spec::template ExternalInterface<Container>;
template <class Spec>
using ContainerOf =
    detail::Container<typename Spec::Concept, Spec::template Model>;

} // namspace detail

template <class Spec_>
class TypeErasure
    : public detail::ExternalInterfaceOf<Spec_, detail::ContainerOf<Spec_>> {
    using Base =
        detail::ExternalInterfaceOf<Spec_, detail::ContainerOf<Spec_>>;

  public:
    using Base::Base;
    using Spec = Spec_;
};

template <class SpecA, class SpecB>
struct MergeSpecs {
    struct Concept : public virtual detail::ConceptOf<SpecA>,
                     public virtual detail::ConceptOf<SpecB> {};

    template <class Holder>
    struct Model
        : public detail::ModelOf<SpecA, detail::ModelOf<SpecB, Holder>>,
          public virtual Concept {
        using Base = detail::ModelOf<SpecA, detail::ModelOf<SpecB, Holder>>;
        using Base::Base;
    };

    template <class Container>
    struct ExternalInterface
        : public detail::ExternalInterfaceOf<
              SpecA, detail::ExternalInterfaceOf<SpecB, Container>> {

        using Base = detail::ExternalInterfaceOf<
            SpecA, detail::ExternalInterfaceOf<SpecB, Container>>;
        using Base::Base;
    };
};

struct GreeterSpec {
    struct Concept {
        virtual ~Concept() = default;
        virtual void greet(const std::string &name) const = 0;
    };

    template <class Holder>
    struct Model : public Holder, public virtual Concept {
        using Holder::Holder;
        virtual void greet(const std::string &name) const override {
            this->Holder::get().greet(name);
        }
    };

    template <class Container>
    struct ExternalInterface : public Container {
        using Container::Container;
        void greet(const std::string &name) const {
            this->Container::get().greet(name);
        }
    };
};

struct OpenerSpec {
    struct Concept {
        virtual ~Concept() = default;
        virtual void open() const = 0;
    };

    template <class Holder>
    struct Model : public Holder, public virtual Concept {
        using Holder::Holder;
        virtual void open() const override {
            this->Model::get().open();
        }
    };

    template <class Container>
    struct ExternalInterface : public Container {
        using Container::Container;
        void open() const {
            this->Container::get().open();
        }
    };
};

using Greeter = TypeErasure<GreeterSpec>;
using Opener = TypeErasure<OpenerSpec>;
using OpenerAndGreeter = TypeErasure<MergeSpecs<OpenerSpec, GreeterSpec>>;

class English {
  public:
    void greet(const std::string &name) const {
        std::cout << "Good day " << name << ". How are you?\n";
    }
    void open() const {
        std::cout << "Squeak...\n";
    }
};

class French {
  public:
    void greet(const std::string &name) const {
        std::cout << "Bonjour " << name << ". Comment ca va?\n";
    }
    void open() const {
        std::cout << "Couic...\n";
    }
};

void open_door(const Opener &o) {
    o.open();
}

void greet_tom(const Greeter &g) {
    g.greet("Tom");
}

void open_door_and_greet_john(const OpenerAndGreeter &g) {
    g.open();
    g.greet("John");
}

int main() {
    English en;
    French fr;

    open_door(en);
    open_door(fr);
    std::cout << "----------------\n";
    greet_tom(en);
    greet_tom(fr);
    std::cout << "----------------\n";
    open_door_and_greet_john(en);
    open_door_and_greet_john(fr);
}