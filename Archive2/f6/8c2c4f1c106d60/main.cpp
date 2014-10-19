#include <iostream>
#include <memory>
#include <string>

namespace detail {

template <class T>
class Holder {
  public:
    Holder(T obj) : data_(std::move(obj)) {}
    virtual ~Holder() = default;
    T &get() { return data_; }
    const T &get() const { return data_; }

  private:
    T data_;
};

template <class Concept, template <class> class Model>
class Container {
  public:
    template <class T>
    Container(T obj)
        : self_(std::make_shared<Model<Holder<T>>>(std::move(obj))) {}

    const Concept &get() const { return *self_.get(); }

  private:
    std::shared_ptr<const Concept> self_;
};

} // detail

template <class Spec>
struct TypeErasure
    : public Spec::template ExternalInterface<
          detail::Container<typename Spec::Concept, Spec::template Model>> {
    using Base = typename Spec::template ExternalInterface<
        detail::Container<typename Spec::Concept, Spec::template Model>>;
    using Base::Base;
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

using Greeter = TypeErasure<GreeterSpec>;

class English {
  public:
    void greet(const std::string &name) const {
        std::cout << "Good day " << name << ". How are you?\n";
    }
};

class French {
  public:
    void greet(const std::string &name) const {
        std::cout << "Bonjour " << name << ". Comment ca va?\n";
    }
};

void greet_tom(const Greeter &g) {
    g.greet("Tom");
}

int main() {
    English en;
    French fr;

    greet_tom(en);
    greet_tom(fr);
}