#include <typeinfo>
#include <vector>
#include <string>

namespace reflection {
    enum access_enum {access_public=0, access_protected, access_private}; //globals have public access
    struct member;
    struct field {
        virtual ~field() {}
        virtual const type* get_parent_type() const =0; //may return null for globals
        virtual const char* get_name(int& out_len) const=0;
        virtual const char* declaraction_file(int& out_len) const=0;
        virtual size_t declaraction_line() const=0;
    };
    struct type : public field {
    };
    struct class_type : public type {
        virtual access_enum get_access() const=0;
        virtual const class_type* const * get_interfaces(int& out_count) const=0;
        virtual const member* const * get_members(int& out_count) const=0;
        virtual bool is_standard_layout() const=0;
        virtual bool is_trivially_copiable() const=0;
        virtual size_t get_size() const=0;
    };
    struct function_type : public type {
        virtual const type* get_return_type() const=0;
        virtual const member* const * const* get_params(int& out_count) const=0;
    };
    struct member : public field {
        virtual const type* get_type() const=0;
        virtual access_enum get_access() const=0;
        virtual bool is_static() const=0;
        virtual bool is_const() const=0;
        virtual bool is_volatile() const=0;
    };
    
    template<class T> const class_type* get_class_reflection();
    template<class T> const function_type* get_function_reflection(T);
    
    template<> const type* get_class_reflection<int>();
    
    
    template<class T>
    struct easy_reflection_class : public class_type {
        const char* name;
        type* parent_type;
        const char* decl_file;
        size_t decl_line;
        access_enum access;
        size_t get_size;
        const type* const* interfaces;
        size_t interface_count;
        const member* const * members;
        size_t members_count;
        bool is_std_layout;
        bool is_trivial_copy;
        
        virtual const type* get_parent_type() const {return parent_type;}
        virtual const char* get_name(int& out_len) {out_len=strlen(name); return name;}
        virtual const char* declaraction_file(int& out_len) const {out_len=strlen(decl_file); return decl_file;}
        virtual size_t declaraction_line() const {return decl_line;}
        virtual access_enum get_access() const {return access;}
        virtual size_t get_size() const {return get_size;}
        virtual const type* const * get_interfaces(int& out_count) const {out_count=interface_count; return interfaces;}
        virtual const member* const * get_members(int& out_count) const  {out_count=member_count; return members;}
        virtual bool is_standard_layout() const {return is_std_layout;}
        virtual bool is_trivially_copiable() const {return is_trivial_copy;}
    };
    template<class T>
    struct easy_reflection_function : public function_type {
        const char* name;
        type* parent_type;
        const char* decl_file;
        size_t decl_line;
        const type* return_type;
        const member* const * params;
        size_t param_count;
        
        virtual const type* get_parent_type() const {return parent_type;}
        virtual const char* get_name(int& out_len) {out_len=strlen(name); return name;}
        virtual const char* declaraction_file(int& out_len) const {out_len=strlen(decl_file); return decl_file;}
        virtual size_t declaraction_line() const {return decl_line;}
        virtual const type* get_return_type() const {return return_type;}
        virtual const member* const * get_params(int& out_count) const {out_count=param_count; return params;}
    };
    template<class T>
    struct easy_reflection_member : public member {
        const char* name;
        type* parent_type;
        const char* decl_file;
        size_t decl_line;
        access_enum access;
        const type* type;
        bool isstatic;
        bool isconst;
        bool isvolatile;
        
        virtual const type* get_parent_type() const {return parent_type;}
        virtual const char* get_name(int& out_len) {out_len=strlen(name); return name;}
        virtual const char* declaraction_file(int& out_len) const {out_len=strlen(decl_file); return decl_file;}
        virtual size_t declaraction_line() const {return decl_line;}
        virtual const type* get_type() const {return type;}
        virtual access_enum get_access() const {return access;}
        virtual bool is_static() const {return isstatic;}
        virtual bool is_const() const {return isconst;}
        virtual bool is_volatile() const {return isvolatile;}
    };
}

//in a CPP file
struct reflected_int_type : public type {
    virtual const type* get_parent_type() const {return nullptr;}
    virtual const char* get_name(int& out_len) {out_len=3; return "int";}
    virtual const char* declaraction_file(int& out_len) const {out_len=0; return "";}
    virtual size_t declaraction_line() const {return 0;}
    virtual const type* const * get_interfaces(int& out_count) const {out_count=0; return nullptr;}
    virtual const member* const * get_members(int& out_count) const;
    virtual bool is_standard_layout() const {return true;}
    virtual bool is_trivially_copiable() const {return true;}
    virtual access_enum get_access() const {return access_public;}
    virtual size_t get_size() const {return sizeof(int);}
} reflected_int;

easy_reflection_member left_int_param = {"left",nullptr,"",0,access_public,&reflected_int,false,false,false};
easy_reflection_member right_int_param = {"right",nullptr,"",0,access_public,&reflected_int,false,false,false};
member* binary_ops[2] = {left_int_param, right_int_param};

easy_reflection_function sig_int_void = {"int",&reflected_int,"",0,nullptr,nullptr,0};
easy_reflection_function sig_int_void_int = {"int",&reflected_int,"",0,nullptr,&right_int_param,1};
easy_reflection_function sig_int_ = {"int",&reflected_int,"",0,nullptr,&right_int_param,1};


