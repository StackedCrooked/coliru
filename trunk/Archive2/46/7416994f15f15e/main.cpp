#include <pthread.h>

class mutex {
    pthread_mutex_t m_mutex;

    // Forbid copy/move
    mutex(const mutex&); // C++11: = delete;
    mutex& operator = (const mutex&); // C++11: = delete;

public:
    mutex() { pthread_mutex_init(&m_mutex, NULL); }
    ~mutex() { pthread_mutex_destroy(&m_mutex); }
    
    void lock() { pthread_mutex_lock(&m_mutex); }
    void unlock() { pthread_mutex_unlock(&m_mutex); }
    bool try_lock() { return pthread_mutex_trylock(&m_mutex) == 0; }
};

class lock_guard {
    mutex& mtx;
public:
    lock_guard(mutex& mtx_) : mtx(mtx_) { mtx.lock(); }
    ~lock_guard() { mtx.unlock(); }
};

template <class> class handle;

template <class T> class storage
{
private:
   T m_var;
   mutex m_mutex;

public:
   storage() : m_var() {}
   storage(const T& var) : m_var(var) {}
   
   friend class handle<T>;
};

template <class T>
class handle {
   T& m_data;
   lock_guard m_lock;

public:
   handle(storage<T>& s) : m_data(s.m_var), m_lock(s.m_mutex) {}
  
   T& operator* () const {
      return m_data;
   }
  
   T* operator -> () const {
      return &m_data;
   }
};

#include<iostream>

struct foo {
    int x;
    int y;
    void do_something_complex() const {
        std::cout << "I'm doing something complex.\n";
    }
};

int main() {
   storage<int> si(0);
   {
      handle<int> bar(si);
      std::cout << *bar << '\n';
      *bar = 42;
      std::cout << *bar << '\n';
   }
   
   std::cout << '\n';
   
   storage<foo> baz;
   {
      handle<foo> hfoo(baz);
      hfoo->x = 42;
      hfoo->y = 13;
      hfoo->do_something_complex();
   }

   std::cout << '\n';

   {
      handle<foo> hfoo(baz);
      std::cout << hfoo->x + hfoo->y << '\n';
   }
}
