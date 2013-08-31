#include <wheels/concurrency/locker_box.h++>

#include <chrono>
#include <exception>
#include <future>
#include <memory>
#include <mutex>
#include <type_traits>
#include <utility>

#include <iostream>

namespace my {
    using std::future_status;

    namespace detail {
        // quick-and-dirty optional-like brick type
        template <typename T>
        struct late_initialized {
        public:
            late_initialized() = default;

            late_initialized(late_initialized&&) = delete;
            late_initialized& operator=(late_initialized&&) = delete;
            
            ~late_initialized() {
                if(initialized) ptr()->~T(); 
            }

            template <typename... Args>
            void initialize(Args&&... args) {
                ::new(ptr()) T(std::forward<Args>(args)...);
                initialized = true;
            }

            explicit operator bool() const { return initialized; }
            
            T& operator*() { return *ptr(); }
            T const& operator*() const { return ptr(); }
            T* operator->() { return *ptr(); }
            T const* operator->() const { return ptr(); }

        private:
            T* ptr() { return static_cast<T*>(static_cast<void*>(&storage)); }
            T const* ptr() const { return static_cast<T*>(static_cast<void*>(&storage)); }

            using storage_type = typename std::aligned_storage<sizeof(T), alignof(T)>::type;
            bool initialized = false;
            storage_type storage;
        };


        template <typename T>
        struct future_shared_state {
        public:
            void wait(std::mutex& mutex) const {
                std::unique_lock<std::mutex> ul(mutex, std::adopt_lock);
                available.wait(ul, [&]{ return state || error; });
                ul.release();
            }

            T& get() {
                if(state) return *state;
                if(error) std::rethrow_exception(error);
                throw std::runtime_error("WTF");
            }

            template <typename U>
            void set_value(U&& value) {
                state.initialize(std::forward<U>(value));
                available.notify_all();
            }
            void set_exception(std::exception_ptr e) {
                error = e;
                available.notify_all();
            }

        private:
            mutable std::condition_variable available;
            late_initialized<T> state;
            std::exception_ptr error;
        };

        template <typename T>
        using future_shared_state_box = wheels::locker_box<future_shared_state<T>>;
    }

    template <typename T> class promise;

    template <typename T>
    struct future {
    public:
        future() noexcept = default;
        future(future&&) noexcept = default;
        future(future const& other) = delete;
    
        ~future() = default;
        
        future& operator=(future&& other) noexcept = default;
        future& operator=(future const& other) = delete;
        
        //shared_future<T> share();
        
        T get() {
            auto old_box = std::move(box);
            for(auto&& state : old_box->open()){
                state.wait(const_cast<std::mutex&>(old_box->mutex())); // ugh, I know what I'm doing :(
                return std::move(state.get());
            }
            WHEELS_UNREACHABLE; // fuck
        }
        
        bool valid() const noexcept { return box != nullptr; }
        
        void wait() const {
            for(auto&& state : box->open()) {
                state.wait();
            }
        }
        
        template<typename Rep, typename Period>
        future_status wait_for(std::chrono::duration<Rep, Period> const& timeout_duration) const;
        template<typename Clock, typename Duration>
        std::future_status wait_until(std::chrono::time_point<Clock, Duration>  const& timeout_time) const;

    private:
        std::shared_ptr<detail::future_shared_state_box<T>> box = nullptr;
        
        friend class promise<T>;
        future(std::shared_ptr<detail::future_shared_state_box<T>> const& box) : box(box) {}
        future(std::shared_ptr<detail::future_shared_state_box<T>>&& box) : box(std::move(box)) {}
    };
    
    template <typename T>
    struct promise {
    public:
        promise()
        : box(std::make_shared<detail::future_shared_state_box<T>>()) {}
        template<typename Alloc>
        promise(std::allocator_arg_t, Alloc const& alloc)
        : box(std::allocate_shared<detail::future_shared_state_box<T>>(alloc)) {}
    	promise(promise&& other) noexcept = default;
    	promise(promise const& other) = delete;
        
        ~promise() = default;
        
        promise& operator=(promise&& other) noexcept = default;
        promise& operator=(promise const& rhs) = delete;
        
        void swap(promise& other) noexcept { box.swap(other.box); }
        
        future<T> get_future() {
            return { box };
        }
        
        void set_value(T const& value) {
            for(auto&& state : box->open()) {
                state.set_value(value);
            }
        }
        void set_value(T&& value) {
            for(auto&& state : box->open()) {
                state.set_value(std::move(value));
            }
        }
        
        //void set_value_at_thread_exit(T const& value);
        //void set_value_at_thread_exit(T&& value);

        void set_exception(std::exception_ptr e) {
            for(auto&& state : box->open()) {
                state.set_exception(std::move(e));
            }
        }
        //void set_exception_at_thread_exit(std::exception_ptr e);

    private:
        std::shared_ptr<detail::future_shared_state_box<T>> box;
    };
    
    template<typename T>
    void swap(promise<T>& lhs, promise<T>& rhs) { lhs.swap(rhs); }
}

namespace std {
    template<typename T, typename Alloc>
    struct uses_allocator<my::promise<T>, Alloc> : true_type {};
}

#include <iostream>
#include <thread>

int main() {
    auto p = std::make_shared<my::promise<int>>();
    std::thread([p]{
        std::cout << "B: waiting one second\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "B: setting 17\n";
        p->set_value(17);
        std::cout << "B: 17 was set\n";
    }).detach();
    auto f = p->get_future();
    std::cout << "A: waiting for future result\n";
    auto r = f.get();
    std::cout << "A: got " << r << '\n';
}