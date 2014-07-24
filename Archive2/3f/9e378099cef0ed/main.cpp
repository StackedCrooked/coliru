#include <iostream>
#include <memory>
#include <vector>

struct Drawable {
    template <typename T>
    Drawable(T t)
        : self_{new DrawableModel<T>(std::move(t))} {
    }

    Drawable(const Drawable &other)
        : self_{other.self_->copy_()} {
    }
    Drawable(Drawable &&) noexcept = default;

    Drawable &operator=(Drawable other) {
        swap(other);
        return *this;
    }

    void swap(Drawable &other) noexcept {
        using std::swap;
        swap(self_, other.self_);
    }

    friend void draw(const Drawable &s) {
        s.self_->draw_();
    }

private:
    struct DrawableConcept {
        virtual ~DrawableConcept() = default;
        virtual DrawableConcept *copy_() const = 0;
        virtual void draw_() const = 0;
    };

    template <typename T>
    struct DrawableModel : DrawableConcept {
        DrawableModel(T t)
            : data_(std::move(t)) {
        }
        DrawableConcept *copy_() const override {
            return new DrawableModel(*this);
        }
        void draw_() const override {
            draw(data_);
        }

    private:
        T data_;
    };

    std::unique_ptr<DrawableConcept> self_;
};

struct Circle {};
struct Triangle {};
struct Square {};

void draw(const Circle &) {
    std::cout << "I'm a Circle!\n";
}

void draw(const Triangle &) {
    std::cout << "I'm a Triangle!\n";
}

void draw(const Square &) {
    std::cout << "I'm a Square!\n";
}

int main() {
    std::vector<Drawable> shapes{Circle(), Square(), Circle(), Triangle(), Triangle(), Circle()};

    for (const auto &shape : shapes) {
        draw(shape);
    }
}