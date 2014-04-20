    // http://stackoverflow.com/questions/23171337/bug-of-gcc-access-control-issue-about-friend-function-in-template-class
    #include <iostream>
    using namespace std;
        
    template <typename T>
    class template_class {
        T v;
        // foo is a friend function of template_class, since template_class is templated, foo is templated
        template <typename FT>
        friend void foo(template_class<FT> & t);
    };
    
    // definition of foo, a templated function friend of templated class template_class
    template <typename T>
    /* friend */ void foo(template_class<T> & t) {
        t.v = 1;    // (1)can access the private member because it's a friend
        cout << t.v << endl;
        template_class<int> t1;
        t1.v = 2;   // (2)this is a different v, the private member variable of t1, a local variable of class type template_class<int>
        cout << t1.v << endl;
        template_class<char> t2;
        t2.v = 'c'; // (3)yet another v, the private member variable of t2, a local variable of class type template_class<char>
        cout << t2.v << endl;
    }
    
    int main() {
        template_class<int> t;  // (4)generate void foo(template_class<int> t)
        foo<int>(t);
        return 0;
    }
