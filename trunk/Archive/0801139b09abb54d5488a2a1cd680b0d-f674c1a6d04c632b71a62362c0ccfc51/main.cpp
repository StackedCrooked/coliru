#include <iostream>
#include <string>
#include <vector>

#include <memory>

namespace mv {
    template <typename T>
    class owning_ptr {
        private:
            T* ptr;
        public:
            // constructors
            explicit constexpr owning_ptr() noexcept
            : ptr(nullptr)
            {}

            /*implicit*/ constexpr owning_ptr(std::nullptr_t) noexcept
            : ptr(nullptr)
            {}
            
            explicit owning_ptr(T* t) noexcept
            : ptr(t)
            {}
            
            /*move*/ owning_ptr(owning_ptr&& o) noexcept
            : ptr(o.release())
            {}
            
            /*move*/ owning_ptr(std::unique_ptr<T>&& o) noexcept
            : ptr(o.release())
            {}

            // destructor
            ~owning_ptr() noexcept
            {
                delete ptr;
            }
            
            // assignment
            owning_ptr& operator=(owning_ptr&& o) noexcept
            {
                reset(o.release());
                return *this;
            }
            
            owning_ptr& operator=(std::nullptr_t) noexcept
            {
                reset();
                return *this;
            }
            
            owning_ptr& operator=(std::unique_ptr<T>&& o) noexcept
            {
                reset(o.release());
                return *this;
            }

            // Modifiers
            T* release() noexcept
            {
                T* ret = ptr;
                ptr = nullptr;
                return ret;
            }
            
            void reset(T* t = nullptr) noexcept
            {
                // delete calls user code, so make sure we are in the proper state before calling
                T* old = ptr;
                ptr = t;
                delete old;
            }
            
            void swap(owning_ptr& o) noexcept
            {
                std::swap(ptr, o.ptr);
            }
            
            // Observers
            explicit operator bool() const noexcept
            {
                return ptr != nullptr;
            }
            
            // main difference from std::unique_ptr here, const overloads return const T*
            T* get() noexcept
            {
                return ptr;
            }
            
            const T* get() const noexcept
            {
                return ptr;
            }
            
            T& operator*() noexcept
            {
                return *get();
            }

            const T& operator*() const noexcept
            {
                return *get();
            }

            T* operator->() noexcept
            {
                return get();
            }

            const T* operator->() const noexcept
            {
                return get();
            }
    };
    
    // comparison
    template <class T1, class T2> bool operator==(const owning_ptr<T1>& t1, const owning_ptr<T2>& t2) { return t1.get() == t2.get(); }
    template <class T1, class T2> bool operator!=(const owning_ptr<T1>& t1, const owning_ptr<T2>& t2) { return t1.get() != t2.get(); }
    template <class T1, class T2> bool operator< (const owning_ptr<T1>& t1, const owning_ptr<T2>& t2) { return t1.get() <  t2.get(); }
    template <class T1, class T2> bool operator<=(const owning_ptr<T1>& t1, const owning_ptr<T2>& t2) { return t1.get() <= t2.get(); }
    template <class T1, class T2> bool operator> (const owning_ptr<T1>& t1, const owning_ptr<T2>& t2) { return t1.get() >  t2.get(); }
    template <class T1, class T2> bool operator>=(const owning_ptr<T1>& t1, const owning_ptr<T2>& t2) { return t1.get() >= t2.get(); }
    
    // swap
    template <class T1, class T2>
    void swap(owning_ptr<T1>& t1, owning_ptr<T2>& t2)
    {
        t1.swap(t2);
    }
}

// hash
namespace std {
  template <typename T>
  struct hash<mv::owning_ptr<T>>: public std::hash<T*>
  {
    size_t operator()(const mv::owning_ptr<T>& p) const
    {
        return std::hash<T*>::operator()(p.get());
    }
  };
}

template <typename T>
struct my_ptr: public std::unique_ptr<T> {
    const T* get() const {
        return std::unique_ptr<T>::get();
    }

    T* get() {
        return std::unique_ptr<T>::get();
    }

    const T& operator*() const {
        return *get();
    };

    T& operator*() {
        return *get();
    };

    const T* operator->() const {
        return get();
    };

    T* operator->() {
        return get();
    };
    
    T* rls() {
        return nullptr;
    }
};

struct x {
    my_ptr<int> m;
    
    x() {
        m.reset(new int(3));
    };
};

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
    mv::owning_ptr<int> a;
    mv::owning_ptr<int> b;
    b = a;
    x tx;
    const x& ty = tx;
    
    //tx.m = std::unique_ptr<int>(new int(3));
    *tx.m = 7;
    
    tx.m.rls();
    
    //*ty.m = 6;
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
    std::cout <<  *ty.m << std::endl;
}
