class bar {
public:
    explicit bar(std::size_t length) : baz(length <= 128 ? array : pointer) {
        
    }

private:
    boost::variant<array_and_length, pointer_and_length> baz;
};
