

void bar(int x) {}

class base {
    void bar() = delete;
};

class derived : public base {
    derived()
    {
        bar(8);
    }
};

int main() {    
}