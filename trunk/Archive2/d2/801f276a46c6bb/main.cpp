#include <pthread.h>

// Approximation of C++11 std::mutex
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

// Approximation of C++11 std::lock_guard<mutex>
class lock_guard {
    mutex& mtx;
public:
    lock_guard(mutex& mtx_) : mtx(mtx_) { mtx.lock(); }
    ~lock_guard() { mtx.unlock(); }
};

template <typename T> class handle;

template <class T> class storage
{
private:
   T m_var;
   mutable mutex m_mutex;

public:
   storage() : m_var() {}
   storage(const T& var) : m_var(var) {}

   friend class handle<T>;
   friend class handle<const T>;
};

template <class T>
class handle {
   T& m_data;
   lock_guard m_lock;
public:
   handle(storage<T>& s) :
       m_data(s.m_var),
       m_lock(s.m_mutex) {}
  
   T& operator* () const {
      return m_data;
   }
  
   T* operator -> () const {
      return &m_data;
   }
};

template <class T>
class handle<const T> {
   const T& m_data;
   lock_guard m_lock;
public:
   handle(const storage<T>& s) :
       m_data(s.m_var),
       m_lock(s.m_mutex) {}

   handle(const storage<const T>& s) :
       m_data(s.m_var),
       m_lock(s.m_mutex) {}
  
   const T& operator* () const {
      return m_data;
   }
  
   const T* operator -> () const {
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
      handle<const foo> hfoo(baz);
      std::cout << hfoo->x + hfoo->y << '\n';
      // non-const access through a const handle correctly results in a compile error:
      // hfoo->x = hfoo->y;
   }
}
