#include <unordered_set>
#include <string>
#include <iterator>
#include <memory>

struct value_base {
    virtual ~value_base() {}
};

template<typename T>
struct value_type : public value_base {
    T value;
    value_type() = default;
    value_type(T v): value(std::move(v)) {}
};


struct arg {
public:
    std::string name;
    std::string desc;
private:
    using value_ptr = std::unique_ptr<value_base>;
    char shorter_name = '\0';
    bool required = false;
    value_ptr value = nullptr;
    friend class options;
public:
    arg() = default;
    arg(std::string name, std::string desc): name(std::move(name)), desc(std::move(desc)) {}
    arg(std::string name, char short_name, std::string desc, value_ptr value = nullptr, bool req = false): 
        name(std::move(name)), desc(std::move(desc)), shorter_name(short_name), required(req), value(std::move(value)) {}
    bool operator==(const arg& a) const {
        return name == a.name;
    }
};

namespace std {
    template<>
    struct hash<arg> {
        size_t operator()(const arg& a) const {
            size_t hash_one = hash<std::string>()(a.name);
            size_t hash_two = hash<std::string>()(a.desc);
            return hash_one ^ (hash_two << 1);
        }
    };
}

struct options {
private:
    std::unordered_set<arg> args;
public:
    options() = default;
    template<size_t N>
    options(arg (&l)[N]): args(std::make_move_iterator(l), std::make_move_iterator(l + N)) {}
};

#include <iostream>

int main() {
    arg args[] = {
        {"Hello", "Test"}, {"One", 'h', "Two"}
    };
    options op(args);
}