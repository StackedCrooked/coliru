template<class type>
class track {
    struct node {
        node* member;        
        void foo() {}
    };
    struct payload : public node {     
        void bar() {this->foo();} //no error   
        void bar2() {foo();}      //error
    };
};

int main() {track<int> a=a;}