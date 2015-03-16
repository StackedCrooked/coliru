    struct A
    {
        virtual void operator()() const = 0;
    };
    
    template<typename Derived>
    struct B : A
    {
        virtual void operator()() const override final
        {
            static_cast<Derived const&>(*this).operator()();
        }
    };
    
    struct C : B<C>
    {
        void operator()() const
        {
            //do something
        }
    };
    
    int main()
    {
        C()();
    }