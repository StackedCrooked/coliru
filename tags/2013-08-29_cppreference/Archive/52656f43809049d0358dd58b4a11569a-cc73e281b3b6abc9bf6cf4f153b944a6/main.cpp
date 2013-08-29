
//exe
void api_function();

struct A {
};

struct B { 
};

int main() {
    try {
        api_function();
    } catch(const A&) {
    } catch(const B&) {
    }
}

//dll
struct C : public A, public B {
};
void api_function() {
    throw C();
}
    


