#include <memory>

template<typename T>
class shared_array_ptr {
public:
    explicit shared_array_ptr(T* ptr) : data(ptr, std::default_delete<T[]>()), offset(0) { }

    shared_array_ptr& operator--() {
        --offset;
        return *this;
    }

    shared_array_ptr operator--(int) {
        auto copy = *this;
        --(*this);
        return copy;
    }

    shared_array_ptr& operator++() {
        ++offset;
        return *this;
    }

    shared_array_ptr operator++(int) {
        auto copy = *this;
        ++(*this);
        return copy;
    }

    T& operator[](std::size_t index) const {
        return data[offset + index];
    }

    T* operator->() const {
        return data + offset;
    }

    T& operator*() const {
        return (*this)[0];
    }

private:
    std::shared_ptr<T> data;
    std::size_t offset;
};

int main() {
    shared_array_ptr<unsigned char> bytecode(new unsigned char[2000]);
    return 0;
}