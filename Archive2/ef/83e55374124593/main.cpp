#include <stdio.h>
#include <stdint.h>

#if 0
#define fwd_hsl_acl_qualify_1(type, unit, arg1)
    fwd_hsl_acl_qualify_##type##
    

static const int unit = 0;
typedef int fwd_hsl_error_t;

typedef enum fwd_hsl_field_group_e {
    FIELD_GROUP_0 = 0,
    FIELD_GROUP_1 = 1    
} fwd_hsl_field_group_t;


fwd_hsl_field_qualify(unit, group,
                      QUALIFY1(DstL3Egress, 10),
                      QUALIFY2(EtherType, 0x0800, 0xFFFF),
                      QUALIFY2(IpProtocol, 0x11, 0xFF),
                      ACTION(ClassDestSet, 10, 10));


fwd_hsl_field_qualify(unit, group,
                      {{DstL3Egress, 10}},
                      {{EtherType, 0x0800, 0xFFFF},
                       {IpProtocol, 0x11, 0xFF}},
                      {{ClassDestSet, 10, 10}});

There are just too many variants for these qualifiers.
Some of them accept uint8, uint16, uint32 and uint64 also!

/* Set match criteria for MplsLabel3Id qualifier. */
extern int bcm_field_qualify_MplsLabel3Id(
    int unit, 
    bcm_field_entry_t entry, 
    uint32 data, 
    uint32 mask);

/* Add an action to a field entry. */
extern int bcm_field_action_add(
    int unit, 
    bcm_field_entry_t entry, 
    bcm_field_action_t action, 
    uint32 param0, 
    uint32 param1);


#endif


typedef enum operation_e {
    QUALIFY_1, QUALIFY_2, ACTION   
} operation_t;

typedef int (*one_arg)(int unit, int entry, uint8_t arg1);
typedef int (*two_arg)(int unit, int entry, uint8_t arg1, uint8_t arg2);


typedef struct operation_s {    
    union {
      one_arg f1;
      two_arg f2;
    } u;
} operation_t;

typedef struct operands_s {
    int n_params;
    union {
        uint64_t params_u64[2];
        uint32_t params_u32[2];
        uint16_t params_u16[2];
        uint8_t  params_u8[2];
    } u;
    uint32_t action;
} operands_t;

typedef struct acl_context_s {
    function_t function;
    operands_t operands;
    operation_t operation;
} context_t;

int main()
{
    printf("%lu\n", sizeof(function_t));
    return 0;
}

