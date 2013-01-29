    template<typename Fun>
    class task {
    public:
        task(Fun fun, T& t) : fun(fun), t(&t) {} // ignores perfect-forwarding like original :P
        
        std::future<ResultOf<Fun(T&)>> get_future() const {
            return promise.get_future();
        }
        
        void operator()() const {
            promise.set_value(fun(*t));
        }
    private:
        Fun fun;
        T* t;
        mutable std::promise<ResultOf<Fun(T&)>> promise;
    };