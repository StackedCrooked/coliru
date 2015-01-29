#define CAT(a, ...) PRIMITIVE_CAT(a, __VA_ARGS__)
#define PRIMITIVE_CAT(a, ...) a ## __VA_ARGS__

#define IIF(c) PRIMITIVE_CAT(IIF_, c)
#define IIF_0(t, ...) __VA_ARGS__
#define IIF_1(t, ...) t

#define COMPL(b) PRIMITIVE_CAT(COMPL_, b)
#define COMPL_0 1
#define COMPL_1 0

#define CHECK_N(x, n, ...) n
#define CHECK(x, ...) CHECK_N(x, 0,)
#define PROBE(x, ...) x, 1,

#define NOT(x) CHECK(PRIMITIVE_CAT(NOT_, x))
#define NOT_0 PROBE(~)

#define BOOL(x) COMPL(NOT(x))
#define IF(c) IIF(BOOL(c))

#define IS_PAREN(...) CHECK(IS_PAREN_PROBE __VA_ARGS__)
#define IS_PAREN_PROBE(...) PROBE(~)

#define EMPTY()
#define DEFER(id) id EMPTY()
#define OBSTRUCT(...) __VA_ARGS__ DEFER(EMPTY)()
#define EXPAND(...) __VA_ARGS__

#define GET_ENUM_VALUE(enum_value, ...) enum_value,
#define GET_ENUM_NAME(enum_value, enum_name) enum_name

#define GET_NEXT_ENUM_VALUE(x, ...) GET_ENUM_VALUE x
#define GET_NEXT_ENUM_NAME(x, ...) GET_ENUM_NAME x
    
#define DISPLAY_NEXT_VALID_ENUM(x, ...) \
IF(IS_PAREN(x)) \
( \
    GET_NEXT_ENUM_VALUE(x) \
) \
IF(IS_PAREN(__VA_ARGS__)) \
( \
        OBSTRUCT(DISPLAY_NEXT_INDIRECT) () \
        ( \
        __VA_ARGS__ \
        ), \
        __VA_ARGS__ \
) \
#define DISPLAY_NEXT_INDIRECT() DISPLAY_NEXT_VALID_ENUM

#define EVAL(...)  EVAL1(EVAL1(EVAL1(__VA_ARGS__)))
#define EVAL1(...) EVAL2(EVAL2(EVAL2(__VA_ARGS__)))
#define EVAL2(...) EVAL3(EVAL3(EVAL3(__VA_ARGS__)))
#define EVAL3(...) EVAL4(EVAL4(EVAL4(__VA_ARGS__)))
#define EVAL4(...) EVAL5(EVAL5(EVAL5(__VA_ARGS__)))
#define EVAL5(...) __VA_ARGS__

 DISPLAY_NEXT_VALID_ENUM((ft_Close=1, "Close"),(ft_High, "High"), (ft_Low, "Low"),(ft_EDSP, "EDSP"),(ft_ARMVM, "ARMVM"))
 EVAL(DISPLAY_NEXT_VALID_ENUM((ft_Close=1, "Close"),(ft_High, "High"), (ft_Low, "Low"),(ft_EDSP, "EDSP"),(ft_ARMVM, "ARMVM")))

#define ENUMERATE(enum_type, enum_type_name, ...) \
enum enum_type{\
EVAL(DISPLAY_NEXT_VALID_ENUM(__VA_ARGS__)) \
};

ENUMERATE(FixingType, "Fixing Hour", 
        (ft_Close=1, "Close"),
        (ft_High, "High"),
        (ft_Low, "Low"),
        (ft_EDSP, "EDSP"),
        (ft_ARMVM, "ARMVM"),
        ft_first=ft_Close, ft_last=ft_ARMVM, ft_default=ft_Close
        )
        
int main()
{
    FixingType f = ft_Close;
    return f;
}
