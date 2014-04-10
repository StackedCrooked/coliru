struct Foo {
    class {
            int value;
        public:
            int & operator = (const int &i) { return value = i; }
            operator int () const { return value; }
    } alpha;

    class {
            float value;
        public:
            float & operator = (const float &f) { return value = f; }
            operator float () const { return value; }
    } bravo;
};