#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <tuple>
#include <array>
#include <set>
#include <deque>
#include <sstream>
#include <cassert>
#include <cstdlib>
#include <type_traits>
#include <utility>
#include <new>

namespace Wide {
    namespace Util {
        struct none_t {} none = {};

        template <typename T>
        struct optional {
        public:
            optional() : present(false) {}

            optional(none_t) : present(false) {}

            optional(T const& t) {
                place(t);
            }
            optional(T&& t) {
                place(std::move(t));
            }

            optional(optional const& that) {
                if(that.present) place(*that);
                else present = false;
            }
            optional(optional&& that) {
                if(that.present) place(std::move(*that));
                else present = false;
            }

            optional& operator=(none_t) {
                if(present) destroy();
                return *this;
            }

            optional& operator=(optional const& that) {
                if(present && that.present) **this = *that;
                else if(present) destroy();
                else if(that.present) place(*that);
                else present = false;
                return *this;
            }
            optional& operator=(optional&& that) {
                if(present && that.present) **this = std::move(*that);
                else if(present) destroy();
                else if(that.present) place(std::move(*that));
                else present = false;
                return *this;
            }

            ~optional() {
                if(present) destroy();
            }

            T& operator*() & { return get(); }
            T const& operator*() const & { return get(); }
            T&& operator*() && { return std::move(get()); }

            T* operator->() { return &get(); }
            T const* operator->() const { return &get(); }

            explicit operator bool() const { return present; }

        private:
            typedef typename std::aligned_storage<sizeof(T), std::alignment_of<T>::value>::type storage_type;

            template <typename Args>
            void place(Args&& args) {
                assert(!present);
                ::new(&storage) T(std::forward<Args>(args));
                present = true;
            }
            void destroy() {
                assert(present);
                get().~T();
                present = false;
            }

            T& get() {
                return *static_cast<T*>(static_cast<void*>(&storage));
            }
            T const& get() const {
                return *static_cast<T const*>(static_cast<void const*>(&storage));
            }

            bool present = false;
            storage_type storage;
        };
    }
} 