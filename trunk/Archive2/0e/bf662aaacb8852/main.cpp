#include <typeinfo>
#include <cxxabi.h>
#include <memory>
#include <string>

static std::string get_typename(const std::type_info& ti) {
    std::string result;
    int status;
    if(std::unique_ptr<char, void(*)(void*)> str{abi::__cxa_demangle(ti.name(), nullptr, nullptr, &status), &std::free})
        result.assign(str.get());
    return result;
}

class FundamentalInfo {
    const abi::__fundamental_type_info* fti;
public:
    FundamentalInfo(const abi::__fundamental_type_info* fti) : fti(fti) {}

    bool is_valid() const { return fti; }
    explicit operator bool() const { return is_valid(); }
    std::string name() const { return get_typename(*fti); }

    static FundamentalInfo from_typeinfo(const std::type_info& ti) { return {dynamic_cast<const abi::__fundamental_type_info*>(&ti)}; }
    template<typename T>
    static FundamentalInfo for_type() { return from_typeinfo(typeid(T)); }
};

class ArrayInfo {
    const abi::__array_type_info* ati;
public:
    ArrayInfo(const abi::__array_type_info* ati) : ati(ati) {}

    bool is_valid() const { return ati; }
    explicit operator bool() const { return is_valid(); }
    std::string name() const { return get_typename(*ati); }

    static ArrayInfo from_typeinfo(const std::type_info& ti) { return {dynamic_cast<const abi::__array_type_info*>(&ti)}; }
    template<typename T>
    static ArrayInfo for_type() { return from_typeinfo(typeid(T)); }
};

class FunctionInfo {
    const abi::__function_type_info* fti;
public:
    FunctionInfo(const abi::__function_type_info* fti) : fti(fti) {}

    bool is_valid() const { return fti; }
    explicit operator bool() const { return is_valid(); }
    std::string name() const { return get_typename(*fti); }

    static FunctionInfo from_typeinfo(const std::type_info& ti) { return {dynamic_cast<const abi::__function_type_info*>(&ti)}; }
    template<typename T>
    static FunctionInfo for_type() { return from_typeinfo(typeid(T)); }
};

class EnumInfo {
    const abi::__enum_type_info* eti;
public:
    EnumInfo(const abi::__enum_type_info* eti) : eti(eti) {}

    bool is_valid() const { return eti; }
    explicit operator bool() const { return is_valid(); }
    std::string name() const { return get_typename(*eti); }

    static EnumInfo from_typeinfo(const std::type_info& ti) { return {dynamic_cast<const abi::__enum_type_info*>(&ti)}; }
    template<typename T>
    static EnumInfo for_type() { return from_typeinfo(typeid(T)); }
};

class SingleInheritanceClassInfo;
class VirtualMultiInheritanceClassInfo;

class ClassInfo {
        const abi::__class_type_info* cti;
protected:
    const abi::__class_type_info* class_info() const { return cti; }

public:
    ClassInfo(const abi::__class_type_info* cti) : cti(cti) {}

    bool is_valid() const { return cti; }
    explicit operator bool() const { return is_valid(); }

    bool is_single() const { return dynamic_cast<const abi::__si_class_type_info*>(cti); }
    bool is_virtual_multiple() const { return dynamic_cast<const abi::__vmi_class_type_info*>(cti); }

    inline SingleInheritanceClassInfo to_single() const;
    inline VirtualMultiInheritanceClassInfo to_virtual_multiple() const;

    std::string name() const { return get_typename(*cti); }

    static ClassInfo from_typeinfo(const std::type_info& ti) { return {dynamic_cast<const abi::__class_type_info*>(&ti)}; }
    template<typename T>
    static ClassInfo for_type() { return from_typeinfo(typeid(T)); }
};

class SingleInheritanceClassInfo : public ClassInfo {
public:
    SingleInheritanceClassInfo(const abi::__si_class_type_info* scti) : ClassInfo(scti) {}

    ClassInfo base_type() const { return {static_cast<const abi::__si_class_type_info*>(class_info())->__base_type}; }

    static SingleInheritanceClassInfo from_typeinfo(const std::type_info& ti) { return {dynamic_cast<const abi::__si_class_type_info*>(&ti)}; }
    template<typename T>
    static SingleInheritanceClassInfo for_type() { return from_typeinfo(typeid(T)); }
};

class BaseClassInfo {
    const abi::__base_class_type_info* ti;
public:
    BaseClassInfo(const abi::__base_class_type_info& ti) : ti(&ti) {}

    bool is_valid() const { return ti; }
    explicit operator bool() const { return is_valid(); }

    ClassInfo base_type() const { return {ti->__base_type}; }

    long offset_flags() const { return ti->__offset_flags; }
    long offset() const { return (offset_flags() >> abi::__base_class_type_info::__offset_shift) << abi::__base_class_type_info::__offset_shift; }
    long flags() const { return (offset_flags() << (sizeof(offset_flags()) - abi::__base_class_type_info::__offset_shift)) >> (sizeof(offset_flags()) - abi::__base_class_type_info::__offset_shift); }

    bool is_virtual() const { return offset_flags() & abi::__base_class_type_info::__virtual_mask; }
    bool is_public() const { return offset_flags() & abi::__base_class_type_info::__public_mask; }

    std::string name() const { return base_type().name(); }
};

class VirtualMultiInheritanceClassInfo : public ClassInfo {
public:
    VirtualMultiInheritanceClassInfo(const abi::__vmi_class_type_info* vcti) : ClassInfo{vcti} {}

    unsigned int flags() const { return static_cast<const abi::__vmi_class_type_info*>(class_info())->__flags; }
    bool is_diamond() const { return flags() & abi::__vmi_class_type_info::__diamond_shaped_mask; }
    unsigned int base_count() const { return static_cast<const abi::__vmi_class_type_info*>(class_info())->__base_count; }

    BaseClassInfo operator[](unsigned int index) const { return {static_cast<const abi::__vmi_class_type_info*>(class_info())->__base_info[index]}; }

    static VirtualMultiInheritanceClassInfo from_typeinfo(const std::type_info& ti) { return {dynamic_cast<const abi::__vmi_class_type_info*>(&ti)}; }
    template<typename T>
    static VirtualMultiInheritanceClassInfo for_type() { return from_typeinfo(typeid(T)); }
};

class TypeInfo;
class PointerInfo;
class PointerToMemberInfo;

class PointerBaseInfo {
    const abi::__pbase_type_info* pbti;
protected:
    const abi::__pbase_type_info* pbase_type_info() const { return pbti; }
public:
    PointerBaseInfo(const abi::__pbase_type_info* pbti) : pbti(pbti) {}

    bool is_valid() const { return pbti; }
    explicit operator bool() const { return is_valid(); }

    unsigned int flags() const { return pbti->__flags; }
    bool is_const() const { return flags() & abi::__pbase_type_info::__const_mask; }
    bool is_volatile() const { return flags() & abi::__pbase_type_info::__volatile_mask; }
    bool is_restrict() const { return flags() & abi::__pbase_type_info::__restrict_mask; }
    bool is_incomplete() const { return flags() & abi::__pbase_type_info::__incomplete_mask; }
    bool is_incomplete_class() const { return flags() & abi::__pbase_type_info::__incomplete_class_mask; }

    inline TypeInfo pointee() const;

    inline PointerInfo to_pointer() const;
    inline PointerToMemberInfo to_pointer_to_member() const;

    std::string name() const { return get_typename(*pbti); }

    static PointerBaseInfo from_typeinfo(const std::type_info& ti) { return {dynamic_cast<const abi::__pbase_type_info*>(&ti)}; }
    template<typename T>
    static PointerBaseInfo for_type() { return from_typeinfo(typeid(T)); }
};

class PointerInfo : public PointerBaseInfo {
public:
    PointerInfo(const abi::__pointer_type_info* pti) : PointerBaseInfo(pti) {}

    static PointerInfo from_typeinfo(const std::type_info& ti) { return {dynamic_cast<const abi::__pointer_type_info*>(&ti)}; }
    template<typename T>
    static PointerInfo for_type() { return from_typeinfo(typeid(T)); }
};

class PointerToMemberInfo : public PointerBaseInfo {
public:
    PointerToMemberInfo(const abi::__pointer_to_member_type_info* ptmti) : PointerBaseInfo(ptmti) {}

    ClassInfo context() const { return {static_cast<const abi::__pointer_to_member_type_info*>(pbase_type_info())->__context}; }

    static PointerToMemberInfo from_typeinfo(const std::type_info& ti) { return {dynamic_cast<const abi::__pointer_to_member_type_info*>(&ti)}; }
    template<typename T>
    static PointerToMemberInfo for_type() { return from_typeinfo(typeid(T)); }
};

class TypeInfo {
    const std::type_info* ti;
public:
    TypeInfo(const std::type_info& ti) : ti(&ti) {}

    bool is_valid() const { return ti; }
    explicit operator bool() const { return is_valid(); }

    bool is_fundamental() const { return {dynamic_cast<const abi::__fundamental_type_info*>(ti)}; }
    FundamentalInfo to_fundamental() const { return {dynamic_cast<const abi::__fundamental_type_info*>(ti)}; }
    bool is_array() const { return {dynamic_cast<const abi::__array_type_info*>(ti)}; }
    ArrayInfo to_array() const { return {dynamic_cast<const abi::__array_type_info*>(ti)}; }
    bool is_function() const { return {dynamic_cast<const abi::__function_type_info*>(ti)}; }
    FunctionInfo to_function() const { return {dynamic_cast<const abi::__function_type_info*>(ti)}; }
    bool is_enum() const { return {dynamic_cast<const abi::__enum_type_info*>(ti)}; }
    EnumInfo to_enum() const { return {dynamic_cast<const abi::__enum_type_info*>(ti)}; }
    bool is_class() const { return {dynamic_cast<const abi::__class_type_info*>(ti)}; }
    ClassInfo to_class() const { return {dynamic_cast<const abi::__class_type_info*>(ti)}; }
    bool is_si_class() const { return {dynamic_cast<const abi::__si_class_type_info*>(ti)}; }
    SingleInheritanceClassInfo to_si_class() const { return {dynamic_cast<const abi::__si_class_type_info*>(ti)}; }
    bool is_vmi_class() const { return {dynamic_cast<const abi::__vmi_class_type_info*>(ti)}; }
    VirtualMultiInheritanceClassInfo to_vmi_class() const { return {dynamic_cast<const abi::__vmi_class_type_info*>(ti)}; }
    bool is_pbase() const { return {dynamic_cast<const abi::__pbase_type_info*>(ti)}; }
    PointerBaseInfo to_pbase() const { return {dynamic_cast<const abi::__pbase_type_info*>(ti)}; }
    bool is_pointer() const { return {dynamic_cast<const abi::__pointer_type_info*>(ti)}; }
    PointerInfo to_pointer() const { return {dynamic_cast<const abi::__pointer_type_info*>(ti)}; }
    bool is_pointer_to_member() const { return {dynamic_cast<const abi::__pointer_to_member_type_info*>(ti)}; }
    PointerToMemberInfo to_pointer_to_member() const { return {dynamic_cast<const abi::__pointer_to_member_type_info*>(ti)}; }

    std::string name() const { return get_typename(*ti); }

    static TypeInfo from_typeinfo(const std::type_info& ti) { return {ti}; }
    template<typename T>
    static TypeInfo for_type() { return from_typeinfo(typeid(T)); }
};

SingleInheritanceClassInfo ClassInfo::to_single() const { return {dynamic_cast<const abi::__si_class_type_info*>(cti)}; }
VirtualMultiInheritanceClassInfo ClassInfo::to_virtual_multiple() const { return {dynamic_cast<const abi::__vmi_class_type_info*>(cti)}; }
TypeInfo PointerBaseInfo::pointee() const { return {*pbti->__pointee}; }
PointerInfo PointerBaseInfo::to_pointer() const { return {dynamic_cast<const abi::__pointer_type_info*>(pbti)}; }
PointerToMemberInfo PointerBaseInfo::to_pointer_to_member() const { return {dynamic_cast<const abi::__pointer_to_member_type_info*>(pbti)}; }

#include <iostream>

inline void show_bases(ClassInfo ci) {
    while(ci) {
        std::cout << ci.name() << " -> ";
        if(auto base = ci.to_single()) {
            std::cout << "(S)";
            ci = base.base_type();
        } else if(auto base = ci.to_virtual_multiple()) {
            for(unsigned int i=0, num=base.base_count(); i < num; ++i) {
                std::cout << "(VM)";
                show_bases(base[i].base_type());
            }
            ci = ClassInfo{nullptr};
        } else {
            ci = ClassInfo{nullptr};
        }
    }
    std::cout << "END\n";
}

inline void show_bases(const std::type_info& ti) {
    return show_bases(ClassInfo::from_typeinfo(ti));
}

#include <locale>

int main() {
    const std::type_info& ti = typeid(std::use_facet<std::ctype<char>(std::cout.getloc()));
    show_bases(typeid(ti));
}