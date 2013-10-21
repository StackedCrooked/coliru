#include <iostream>
    using namespace std;

    class Members
    {
        mutable int x;
        public:
            Members();
            void member();
            void member() const;
    };

    Members::Members()
    {}
    void Members::member()
    {
        cout << "non const member\n";
    }
     void Members::member() const
    {
        x = 15;
        cout << "const member\n";
    }
    
        int main()
    {
        Members const constObject;
        Members       nonConstObject;

        constObject.member();
        nonConstObject.member();
    }
 