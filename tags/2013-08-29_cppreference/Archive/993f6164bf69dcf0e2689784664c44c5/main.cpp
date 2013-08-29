template<class type>
class track {
    struct node {
        node* member;        
        void foo() {}
    };
    struct payload : public node {        
        void bar() {foo();}
    };
};

int main() {track<int> a=a;}