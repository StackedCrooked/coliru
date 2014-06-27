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

int main()
{
    foo<int> f;
    f.changeValue(42);
}
