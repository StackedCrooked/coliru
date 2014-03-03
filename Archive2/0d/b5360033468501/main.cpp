    #include <cstdlib>
    #include <iostream>
    #include <map>
    #include <string>
    #include <algorithm>

    using namespace std;

    class A
    {
    private:
        string m_memberA;

    public:
        explicit A(string inp):m_memberA(inp){}
        int GetValue()
        {
            return m_memberA.size();
        }
    };

    class B
    {
    private:
        int m_memberB;
    public:
        explicit B(int inp):m_memberB(inp){}
    };

    class C
    {
    private:
        double m_memberC;
    public:
        explicit C(double inp):m_memberC(inp){}
    };

    class functor
    {
    private:
        A* m_member;
    public:
        explicit functor(A* inp): m_member(inp){}

        bool operator()(const std::pair<A* const, B*>& iter) const
        {
             return (m_member->GetValue() == (iter.first)->GetValue());
        }

        bool operator()(const std::pair<A* const, C*>& iter) const
        {
            return (m_member->GetValue() == (iter.first)->GetValue());
        }
    };

    int main(int argc, char *argv[])
    {
        A* obj_ptr_A1 = new A("Hello");
        A* obj_ptr_A2 = new A("MyWorld");

        B* obj_ptr_B1 = new B(22);
        B* obj_ptr_B2 = new B(11);

        C* obj_ptr_C1 = new C(5.5);
        C* obj_ptr_C2 = new C(9.5);

        map<A*, B*> myMap1;
        myMap1.insert(make_pair(obj_ptr_A1, obj_ptr_B1));
        myMap1.insert(make_pair(obj_ptr_A2, obj_ptr_B2));

        map<A*, C*> myMap2;
        myMap2.insert(make_pair(obj_ptr_A1, obj_ptr_C1));
        myMap2.insert(make_pair(obj_ptr_A2, obj_ptr_C2));

        if(find_if(myMap1.begin(), myMap1.end(), functor(obj_ptr_A2)) != myMap1.end())
        {
            cout << "Found" << endl;
        }

        if(find_if(myMap2.begin(), myMap2.end(), functor(obj_ptr_A2)) != myMap2.end())
        {
            cout << "Found" << endl;
        }

        system("PAUSE");
        return EXIT_SUCCESS;
    }