template <typename Derived>
struct Base
{
    Derived& operator+=(const Derived& other)
    {
        //....
        return *self();
    }
    friend Derived operator+(Derived left, const Derived& other)
    {
        return left += other;
    }
private:
    Derived* self() {return static_cast<Derived*>(this);}
};

struct Thing : public Base<Thing> 
{};


int main() {
    Thing a, b;
    Thing c = a + b;
}