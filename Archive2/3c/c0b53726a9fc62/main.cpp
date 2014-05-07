
    #define DEFINE_STRUCT_WITH_KNOWN_PACKED_SIZE(StructName, StructBody)\
    struct StructName StructBody\
    struct __attribute__ ((__packed__)) StructName##_packed StructBody

    
    #define GET_PACKED_SIZE(StructName) sizeof(struct StructName##_packed)

    DEFINE_STRUCT_WITH_KNOWN_PACKED_SIZE(Name, {
       int a;
       char ch;
    };)

    #include <stdio.h>

    int main() {
        printf("%lu", GET_PACKED_SIZE(Name));
    }
    