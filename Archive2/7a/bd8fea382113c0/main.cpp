#include <utility>
#include <typeindex>
#include <type_traits>
#include <algorithm>
#include <iostream>

    namespace details {
    template<class T>using type=T;
    struct some_meta {
      type<void(void*)>* destroy;
      type<void(void* dest, void const* src)>* copy;
      type<void(void* dest, void* src)>* move;
      std::type_index type;
      size_t size;
      size_t align;
      template<class T> static some_meta const* get() {
        static const some_meta retval( create<T>() );
        return &retval;
      };
      private:
      template<class T> static some_meta create() {
        return {
            [](void* p){ ((T*)p)->~T(); },
            [](void* out, void const* in){ new(out)T(*(T*)in); },
            [](void* dest, void* src) { new(dest)T(std::move(*(T*)src)); },
            typeid(T),
            sizeof(T),
            alignof(T)
        };
      }
    };
    }
    
    template<class>struct emplace_as{};

    template< std::size_t size, std::size_t align >
    struct some {
      template<size_t, size_t> friend struct some;
      template<class T> struct can_store :
        std::integral_constant< bool, (alignof(T) <= align && sizeof(T) <= size) >
      {};

      template<size_t x, size_t a>
      static bool can_fit( some<x,a> const& o ) {
        if (x<=size && a<=align) return true; // should cause optimizations
        if (!o.meta) return true;
        if (o.meta->size > size) return false;
        if (o.meta->align > align) return false;
        return true;
      }
    private:
      std::aligned_storage_t<size, align> data;
      details::some_meta const* meta = nullptr;
    public:
      // true iif we are (exactly) a T
      template<class T>
      bool is() const {
          return meta && (meta->type == typeid(T));
      }
      
      explicit operator bool()const { return meta!=nullptr; }
      
      template<class T>
      T* unsafe_get() { return reinterpret_cast<T*>(&data); }

      template<class T>
      T* get() { if (is<T>()) return unsafe_get<T>(); else return nullptr; }

      void clear() { if (meta) meta->destroy(&data); meta = nullptr; }
      
      template<class T, class... Args>
      std::enable_if_t< can_store<T>{} >
      emplace(Args&&...args) {
        clear();

        new(&data) T(std::forward<Args>(args)...);
        meta = details::some_meta::get<T>();
      }
      some()=default;
      some(some const& o) {
        *this = o;
      }
      some(some const&&o):some(o){}
      some(some&o):some(const_cast<some const&>(o)){}
      some(some&& o) {
        *this = std::move(o);
      }
      
      some& operator=(some const&o) {
        if (this == &o) return *this;
        clear();
        if (o.meta) {
          o.meta->copy( &data, &o.data );
          meta=o.meta;
        }
        return *this;
      }        
      some& operator=(some &&o) {
        if (this == &o) return *this;
        clear();
        if (o.meta) {
          o.meta->move( &data, &o.data );
          meta=o.meta;
          o.clear();
        }
        return *this;
      }
      some& operator=(some const&&o) { return *this=o; }
      some& operator=(some &o) { return *this=const_cast<some const&>(o); }

      // from non-some:
      template<class T,class=std::enable_if_t<can_store<std::decay_t<T>>{}>>
      some(T&& t){
        emplace<std::decay_t<T>>(std::forward<T>(t));
      }
      template<class T, class...Args,class=std::enable_if_t<can_store<T>{}>>
      some( emplace_as<T>, Args&&...args ){
        emplace<T>(std::forward<Args>(args)...);
      }
      template<class T,class=std::enable_if_t<can_store<std::decay_t<T>>{}>>
      some& operator=(T&&t){
        emplace<std::decay_t<T>>(std::forward<T>(t));
        return *this;
      }

      template<size_t x, size_t a>
      bool load_from( some<x,a> const& o ) {
        if ((void*)&o==this) return true;
        if (!can_fit(o)) return false;
        clear();
        if (o.meta) {
          o.meta->copy( &data, &o.data );
          meta=o.meta;
        }
        return true;
      }
      template<size_t x, size_t a>
      bool load_from( some<x,a> && o ) {
        if ((void*)&o==this) return true;
        if (!can_fit(o)) return false;
        clear();
        if (o.meta) {
          o.meta->move( &data, &o.data );
          meta=o.meta;
          o.clear();
        }
        return true;
      }
      ~some() { clear(); }
    };

    template<class T, class...Ts>
    using some_that_fits = some< (std::max)({sizeof(T),sizeof(Ts)...}), (std::max)({alignof(T),alignof(Ts)...}) >;
    
    struct big { char x[1000]; };
    struct small { char x[8]; };
    struct noisy { ~noisy() { std::cout << "bang\n"; } };
int main() {
    some_that_fits<double,int> test;
    test = 'a';
    char* c = test.get<char>();
    std::cout << (void*)c << "\n";
    if (c)
      std::cout << *c << "\n";
    std::cout << decltype(test)::can_store<big>{} << "\n";
    test = small{};
    test = noisy{};
    std::cout << "...\n";
    some_that_fits<noisy> test2=emplace_as<noisy>{};
    test.load_from(test2);
    std::cout<<"...\n";
}
    