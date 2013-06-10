template<int C>
        union
        Vector 
        {
        public:

            static_assert(C >= 2 and C <= 4, "ELEMENT_COUNT must be 2~4.");

            int  v[C];

            ////

            struct
            Utility
            {
                inline static Vector const     add(Vector const a, Vector const b){ return b;};
            };
        };

int main(void)
{
    Vector<2>   v1, v2;
Vector<2>   v3  =   Vector<2>::Utility::add(v1, v2);
}