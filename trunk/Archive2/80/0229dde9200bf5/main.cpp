    #include <iostream>
    using namespace std;

    class Base
    {
        private:
            virtual void hello() const
            {
                cout << "base hello\n";
            }
        public:
            void process() const
            {
                this->hello();
            }
    };
    class Derived: public Base
    {
        private:
            void hello() const
            {
                cout << "derived hello\n";
            }
    };
    int main()
    {
        Base const &r = Derived(); // because of LSP

        r.process();
    }