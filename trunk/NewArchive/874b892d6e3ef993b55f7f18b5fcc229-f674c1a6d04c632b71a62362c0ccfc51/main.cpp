class value
{
public:
    virtual ~value() {}
private:
    struct inner { char c_; };
    inner i_;
protected:
    inner f() { return i_; }
};

class derived_value : public value
{
public:
    void g() { inner i = f(); }
};

int main() { }
