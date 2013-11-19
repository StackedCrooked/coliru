#include <functional>
#include <map>
#include <iostream>
#include <boost/variant.hpp>

class DynamicVariant;

using DynamicFunction = std::function<void(DynamicVariant &)>;

using DynamicType = boost::variant<
    char,
    int,
    double,
    std::string,
    DynamicVariant,
    DynamicFunction
>;

class DynamicVariant
    : private std::map<std::string, DynamicType> {
    using super = std::map<std::string, DynamicType>;
    
public:
    
    void print(std::ostream &, const std::string & = std::string()) const;
    
    bool has(const std::string &index) const {
        return super::find(index) != super::end();
    }
    
    template<typename T>
    T *is(const std::string &index) {
        const auto &f = super::find(index);
        return (f == super::end())
                ? nullptr
                : boost::get<T>(&f->second);
    }
    
    template<typename T>
    const T *is(const std::string &index) const {
        return const_cast<DynamicVariant *>(this)->is<T>(index);
    }
    
    template<typename T>
    DynamicVariant &set(const std::string &index, T &&v) {
        super::operator[](index) = v;
        return *this;
    }
    
    DynamicVariant &unset(const std::string &index) {
        super::erase(index);
        return *this;
    }
    
    const DynamicVariant &nested(const std::string &index) const {
        return boost::get<DynamicVariant>(super::at(index));
    }
    
    DynamicVariant &nested(const std::string &index) {
        return boost::get<DynamicVariant>(super::operator[](index));
    }
    
    template<typename T, typename T2>
    const DynamicVariant &get(const std::string &index, T &v, T2 &&deflt) const {
        const T *p = is<T>(index);
        v = p ? *p : deflt;
        return *this;
    }
    
    template<typename T>
    const DynamicVariant &get(const std::string &index, T &v) const {
        return get(index, v, T());
    }
    
    std::function<DynamicVariant(DynamicVariant &)> callable(const std::string &);
    template<typename R>
    const R &at(const std::string &index) const {
        return boost::get<R>(super::at(index));
    }

    struct Printer;
    
};

std::function<DynamicVariant(DynamicVariant &)> DynamicVariant::callable(const std::string &index) {
    return [this, index](DynamicVariant &args) -> DynamicVariant {
        DynamicVariant env;
        env["__args"] = args;
        env["__this"] = *this;
        boost::get<DynamicFunction &>(super::at(index))(env);
        DynamicVariant result;
        env.get("__result", result);
        return result;
    };
}

class DynamicVariant::Printer : public boost::static_visitor<> {
    std::ostream &os;
public:
    Printer(std::ostream &os_) : os(os_) {}
    template<typename T>
    void operator()(const T &v) const {
        os << v;
    }
    void operator()(const DynamicFunction &) const {
        os << "[](DynamicVariant &) -> void";
    }
    void operator()(const DynamicVariant &v) const {
        v.print(os);
    }
};

void DynamicVariant::print(std::ostream &os, const std::string &sep) const {
    os << "{ ";
    for (const auto &elem : *this) {
        os << elem.first << ": ";
        if (boost::get<const std::string>(&elem.second)) os << '"';
        boost::apply_visitor(Printer(os), elem.second);
        if (boost::get<const std::string>(&elem.second)) os << '"';
        os << "; ";
    }
    os << "}" << sep;
}

#include <cassert>

int main()
{
    DynamicVariant v;
    v.set("atu", 42);
    v.set("pi", 3.14);

    DynamicVariant other;
    other.set("greet", std::string("hello, world"));
    v.print(std::cout, "\n");
    other.print(std::cout, "\n");
    
    v.set("inside", other);
    v.print(std::cout, "\n");
    v.nested("inside").set("more", 1e6f)
                      .set("greet", "hi!");
    v.print(std::cout, "\n");
    
    v.set("sayhello", [](DynamicVariant &env) -> void {
        std::cout << "Salve " << env.nested("__args").at<std::string>("name") << '!' << std::endl;
    });
    DynamicVariant my_args;
    std::string my_result;
    my_args.set("name", "Martin");
    my_args.print(std::cout, "\n");
    v.callable("sayhello")(my_args);
    
    v.set("sayhello", [](DynamicVariant &env) -> void {
        const &args(env.nested("__args"));
        const auto &instance(env.nested("__this"));
        const auto &fullname(args.at<std::string>("first") + " " + args.at<std::string>("last"));
        std::cout << fullname << ": " << instance.nested("inside").at<std::string>("greet") << std::endl;
        DynamicVariant result;
        result.set("fullname", fullname);
        env.set("__result", result);
    });
    DynamicVariant other_args{my_args};
    other_args.print(std::cout, "\n");
    other_args.unset("name");
    other_args.print(std::cout, "\n");
    other_args.set("first", "Martin");
    other_args.set("last", "Weitzel");
    DynamicVariant ret = v.callable("sayhello")(other_args);
    return 0;
    ret.get("fullname", my_result, "(no result)");
    std::cout << my_result << std::endl;
}
