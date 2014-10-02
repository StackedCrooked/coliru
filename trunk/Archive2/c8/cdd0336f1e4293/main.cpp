class _ref
{
public:
    _ref() {}
    _ref(const _ref& that) {}
    virtual ~_ref() = 0;
};
_ref::~_ref() {}

template <typename T>
class ref : public _ref
{
    template <typename U>
    friend class ref;
    
protected:
    ref(const _ref& that) {}

public:
    ref() {}
    ref(const ref<T>& that) {}
    virtual ~ref() {}

    template <typename U>
    ref<U> tryCast()
    {
        bool valid = true;
        //perform some check to make sure the conversion is valid

        if (valid)
            return ref<U>(*this); //ref<T> cannot access protected constructor declared in class ref<U>
        else
            return ref<U>();
    }
};

int main()
{
    ref<int> i;
    ref<char> c = i.tryCast<char>();
}
