#include <iostream>
#include <string>
#include <sstream>
#include <vector>

namespace JNI {
    struct Type;
    struct Signature;

    namespace Detail {
        enum Kind {
            Boolean, Byte, Char, Short, Int, Long, Float, Double, Class, Void, Wrapped
        };

        std::string make_name(Kind kind, std::string name) {
            switch (kind) {
                case Boolean: return "Z";
                case Byte:    return "B";
                case Char:    return "C";
                case Short:   return "S";
                case Int:     return "I";
                case Long:    return "J";
                case Float:   return "F";
                case Double:  return "D";
                case Class:   return "L" + name + ";";
                case Void:    return "V";
                case Wrapped: return name;
            }

            return "<BUG>";
        }

        struct SignatureGlue {
            explicit SignatureGlue(Type);
            SignatureGlue operator,(Type) const;

            std::vector<Type> types;
        };
    }

    struct Type {
        explicit Type(Detail::Kind, std::string = "", bool = false);
        Signature operator()(Type) const;
        Signature operator()(Detail::SignatureGlue) const;
        Detail::SignatureGlue operator,(Type) const;

        std::string name;
    };

    struct Signature {
        Signature(Type, Detail::SignatureGlue);
        std::string ToString() const;

        Type return_;
        std::vector<Type> arguments;
    };

    namespace Detail {
        SignatureGlue::SignatureGlue(Type type) : types(1, type) {
        }

        SignatureGlue SignatureGlue::operator,(Type type) const {
            auto copy = *this;
            copy.types.push_back(type);
            return copy;
        }
    }

    Signature::Signature(Type return_, Detail::SignatureGlue arguments) : return_(return_), arguments(arguments.types) {
    }

    std::string Signature::ToString() const {
        std::stringstream ss;
        ss << "(";
        for (auto type : arguments) {
            ss << type.name;
        }
        ss << ")" << return_.name;
        return ss.str();
    }

    Type::Type(Detail::Kind kind, std::string name, bool is_array) : name(Detail::make_name(kind, name)) {
        if (is_array) {
            this->name = "[" + this->name;
        }
    }

    Signature Type::operator()(Type other) const {
        return (*this)(Detail::SignatureGlue(other));
    }

    Signature Type::operator()(Detail::SignatureGlue other) const {
        return Signature(*this, other);
    }

    Detail::SignatureGlue Type::operator,(Type other) const {
        return Detail::SignatureGlue(*this), other;
    }

    Type Class(std::string name) {
        return Type(Detail::Class, name);
    }

    Type Array(Type other) {
        return Type(Detail::Wrapped, other.name, true);
    }

    Type Int = Type(Detail::Int);
    Type Void = Type(Detail::Void);
    Type Long = Type(Detail::Long);
    Type String = Class("java/lang/String");
}

int main() {
    JNI::Signature sig = JNI::Void((JNI::Array(JNI::Int), JNI::String, JNI::Class("java/lang/Integer")));
    JNI::Signature sig2 = JNI::Long((JNI::Int, JNI::String, JNI::Array(JNI::Int)));
    std::cout << sig.ToString() << "\n";
    std::cout << sig2.ToString() << "\n";
}
