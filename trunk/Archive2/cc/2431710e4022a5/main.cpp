#include <atomic>
#include <cassert>
#include <cstddef>
#include <deque>
#include <functional>
#include <future>
#include <iostream>
#include <thread>

                                                                                                                                                                                                                                                                                                template <std::size_t N> class stack_store { public: stack_store() = default;  stack_store(stack_store const&) = delete;  stack_store& operator=(stack_store const&) = delete;  char* allocate(std::size_t n) { assert(pointer_in_buffer(ptr_) && "stack_allocator has outlived stack_store");  n = align(n);  if (buf_ + N >= ptr_ + n) { auto r(ptr_);  ptr_ += n;  return r; } else { std::cout << "using operator new " << n << std::endl; return static_cast<char*>(::operator new(n)); } }  void deallocate(char* const p, std::size_t n) noexcept { assert(pointer_in_buffer(ptr_)&& "stack_allocator has outlived stack_store");  if (pointer_in_buffer(p)) { n = align(n);  if (p + n == ptr_) { ptr_ = p; } } else { std::cout << "using operator delete " << n << std::endl; ::operator delete(p); } }  void reset() noexcept { ptr_ = buf_; }  static constexpr ::std::size_t size() noexcept { return N; }  ::std::size_t used() const { return ::std::size_t(ptr_ - buf_); }  private: static constexpr ::std::size_t align(::std::size_t const n) noexcept { return (n + (alignment - 1)) & -alignment; }  bool pointer_in_buffer(char* const p) noexcept { return (buf_ <= p) && (p <= buf_ + N); }  private: static constexpr auto const alignment = alignof(max_align_t);  char* ptr_ {buf_};  alignas(max_align_t) char buf_[N];};  template <class T, std::size_t N> class stack_allocator { public: using store_type = stack_store<N>;  using size_type = ::std::size_t;  using difference_type = ::std::ptrdiff_t;  using pointer = T* ; using const_pointer = T const* ;  using reference = T& ; using const_reference = T const& ;  using value_type = T;  template <class U> struct rebind { using other = stack_allocator<U, N>; };  stack_allocator() = default;  stack_allocator(stack_store<N>& s) noexcept : store_(&s) { }  template <class U> stack_allocator(stack_allocator<U, N> const& other) noexcept : store_(other.store_) { }  stack_allocator& operator=(stack_allocator const&) = delete;  T* allocate(::std::size_t const n) { return static_cast<T*>(static_cast<void*>( store_->allocate(n * sizeof(T)))); }  void deallocate(T* const p, ::std::size_t const n) noexcept { store_->deallocate(static_cast<char*>(static_cast<void*>(p)), n * sizeof(T)); }  template <class U, class ...A> void construct(U* const p, A&& ...args) { new(p) U(::std::forward<A>(args)...); }  template <class U> void destroy(U* const p) { p->~U(); }  template <class U, std::size_t M> inline bool operator==(stack_allocator<U, M> const& rhs) const noexcept { return store_ == rhs.store_; }  template <class U, std::size_t M> inline bool operator!=(stack_allocator<U, M> const& rhs) const noexcept { return !(*this == rhs); }  private: template <class U, std::size_t M> friend class stack_allocator;  store_type* store_ {}; };  template<typename T = char, std::size_t N> stack_allocator<T, N> make_stack_allocator(stack_store<N>& store) { return stack_allocator<T, N>(store); }  
struct DispatchThingy
{
    DispatchThingy() :
        mQuit{false},
        mDispatcherThread([=]{ dispatcher_thread(); })
    {
    }
    
    DispatchThingy(const DispatchThingy&) = delete;
    DispatchThingy& operator=(const DispatchThingy&) = delete;

    ~DispatchThingy()
    {
        mQuit = true;
        mDispatcherThread.join();
    }

    template<typename F>
    auto dispatch(F&& f) -> decltype(f())
    {
        typedef decltype(f()) R;
        
        
        /** THE INTERESTING STUFF IS HERE */
        stack_store<256> storage;
        auto stack_allocator = make_stack_allocator(storage);
        std::packaged_task<R()> task(std::allocator_arg, stack_allocator, std::forward<F>(f));
        
        mQueue.push_back([&] {
            return task();
        });
        
        return task.get_future().get(); // this must be blocking when using stack allocator
    }

private:
    void dispatcher_thread()
    {
        for (;!mQuit;)
        {
            while (!mQueue.empty())
            {
                auto front = std::move(mQueue.front());
                mQueue.pop_front();
                front();
            }
            
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    }

    std::atomic<bool> mQuit;
    std::deque<std::function<void()>> mQueue;
    std::thread mDispatcherThread;
};



int main(int argc, char** argv)
{
    DispatchThingy stack;
    
    std::cout << stack.dispatch([=]{ return std::string() + "stacked allocator is crooked awesome"; }) << std::endl;
}
