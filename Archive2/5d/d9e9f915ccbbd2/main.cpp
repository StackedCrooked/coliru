
        template<typename T>
        struct  Aligned
        {
            Aligned() : t() {}
            alignas(128) T t;
        };
        
        
        int main()
        {
            Aligned<int> n;
            Aligned<int> m;
        }