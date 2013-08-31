#include <cassert>
#include <memory>
#include <new>
#include <cstdint>

struct raw_memory_buffer {
    raw_memory_buffer(std::size_t size)
    : ptr(::operator new(size)),
      size_(size) {};

    // noncopyable
    raw_memory_buffer(raw_memory_buffer&& that)
    : ptr(that.ptr), size_(that.size_) { that.ptr = nullptr; }

    raw_memory_buffer& operator=(raw_memory_buffer&& that) {
        raw_memory_buffer other(std::move(that));
        std::swap(ptr, other.ptr);
        std::swap(size_, other.size_);
        return *this;
    }

    void* get() const { return ptr; }
    std::size_t space() const { return size_; }

    ~raw_memory_buffer() {
        if(ptr) ::operator delete(ptr);
    }

private:
    void* ptr;
    std::size_t size_;
};

template <typename T, std::size_t Alignment = 32>
struct aligned_array {
    static_assert(Alignment >= alignof(T), "requested alignment is too small");

    aligned_array(std::size_t count)
    : buffer(count * sizeof(T) + Alignment - 1),
      aligned_ptr(get_aligned_ptr()) {
        std::uninitialized_fill(aligned_ptr, aligned_ptr + count, T()); // or similar
    }

private:
    raw_memory_buffer buffer;
    T* aligned_ptr;
    std::size_t count;
    
    T* get_aligned_ptr() const {
        void* ptr = buffer.get();
        void* aligned = reinterpret_cast<void*>((reinterpret_cast<std::intptr_t>(ptr) + Alignment - 1) & ~(Alignment - 1));
        return static_cast<T*>(aligned);
    }
};

int main() {}