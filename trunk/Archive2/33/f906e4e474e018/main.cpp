struct foo
{
    virtual void f0() noexcept final {};
    virtual void f1() final noexcept {};
};

int main() {}