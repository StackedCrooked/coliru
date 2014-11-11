    class apple;
    
    class fruit {
    public:
        int i;
        void set(apple a);
    };
    
    class apple {
    public:
        int j;
        void set(fruit f);
    };
    
    void fruit::set(apple a)
    {
        i = a.j;
    }
    void apple::set(fruit f)
    {
        j = f.i;
    }