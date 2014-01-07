    #include <vector>
    #include <iostream>
     
    class String
    {
    public:
    //! default constructor
    String();
     
    //! constructor taking C-style string i.e. a char array terminated with'\0'.
    explicit String(const char * const c);
     
    //! copy constructor
    explicit String(const String& s);
     
    //! move constructor
    String(String&& s) noexcept;
     
    //! operator =
    String& operator = (const String& rhs);
     
    //! move operator =
    String& operator = (String&& rhs) noexcept;
     
    //! destructor
    ~String();
     
    //! members
    char* begin() const { return elements; }
    char* end() const { return first_free; }
     
    std::size_t size() const {return first_free - elements; }
    std::size_t capacity() const {return cap - elements; }
     
    private:
     
    //! data members
    char* elements;
    char* first_free;
    char* cap;
     
    std::allocator<char> alloc;
     
    //! utillities for big 3
    void free();
     
    };
     
    //! default constructor
    String::String():
    elements (nullptr),
    first_free (nullptr),
    cap (nullptr)
    {}
     
    //! copy constructor
    String::String(const String &s)
    {
    char* newData = alloc.allocate(s.size());
    std::uninitialized_copy(s.begin(), s.end(), newData);
     
    elements = newData;
    cap = first_free = newData + s.size();
     
    std::cout << "Copy constructing......\n";
    }
     
    //! move constructor
    String::String(String &&s) noexcept :
    elements(s.elements), first_free(s.first_free), cap(s.cap)
    {
    s.elements = s.first_free = s.cap = nullptr;
    std::cout << "Move constructing......\n";
    }
     
    String::~String()
    {
    // leaky leaky
    }
     
    String& String::operator = (String&& rhs) noexcept
    {
    String temp(rhs);
    std::swap(elements, temp.elements);
    std::swap(first_free, temp.first_free);
    std::swap(cap, temp.cap);
    return *this;
    }
     
    int main()
    {
    std::vector<String> v;
    String s;
    for (unsigned i = 0; i != 4; ++i)
    v.push_back(s);
     
    return 0;
    }
     