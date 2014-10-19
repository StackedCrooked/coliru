#include <iostream>
#include <memory>
#include <string>

class Greeter {
  public:
    template <class T>
    Greeter(T data) : self_(std::make_shared<Model<T>>(data)) {}

    void greet(const std::string &name) const { self_->greet(name); }

  private:
    struct Concept {
        virtual ~Concept() = default;
        virtual void greet(const std::string &) const = 0;
    };
    template <class T>
    class Model : public Concept {
      public:
        Model(T data) : data_(data) {}
        virtual void greet(const std::string &name) const override {
            data_.greet(name);
        }

      private:
        T data_;
    };

    std::shared_ptr<const Concept> self_;
};

class OpenerAndGreeter {
  public:
    template <class T>
    OpenerAndGreeter(T data) : self_(std::make_shared<Model<T>>(data)) {}

    void open() const { self_->open(); }
    void greet(const std::string &name) const { self_->greet(name); }

  private:
    struct Concept {
        virtual ~Concept() = default;
        virtual void open() const = 0;
        virtual void greet(const std::string &) const = 0;
    };
    template <class T>
    class Model : public Concept {
      public:
        Model(T data) : data_(data) {}
        virtual void open() const override { data_.open(); }
        virtual void greet(const std::string &name) const override {
            data_.greet(name);
        }

      private:
        T data_;
    };

    std::shared_ptr<const Concept> self_;
};

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

void greet_tom(const Greeter &g) {
    g.greet("Tom");
}

void open_door_and_greet_john(const OpenerAndGreeter &g) {
    g.open();
    g.greet("John");
}

int main() {
    greet_tom(English{});
    greet_tom(French{});
    std::cout << "----------------\n";
    open_door_and_greet_john(English{});
    open_door_and_greet_john(French{});
}