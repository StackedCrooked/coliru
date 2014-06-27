template <typename T>
class foo {
    public:
        void changeValue(T) const;
    private:
        T value;
};

template <typename T>
void foo<T>::changeValue(T newValue) const {
    value = newValue;
}

struct SpecialValue
{
    const SpecialValue& operator=(const SpecialValue &other) const
    {
        return *this;
    }
};

int main()
{
    foo<SpecialValue> f;
    f.changeValue(SpecialValue{});
}
