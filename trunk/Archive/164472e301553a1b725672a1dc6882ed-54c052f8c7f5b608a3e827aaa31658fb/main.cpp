#include <boost/preprocessor.hpp>

#define HEAD BOOST_PP_SEQ_HEAD
#define TAIL BOOST_PP_SEQ_TAIL
#define EACH BOOST_PP_SEQ_FOR_EACH 
#define ELEM BOOST_PP_SEQ_ELEM
#define FIRST(Seq) ELEM(0, Seq)
#define SECOND(Seq) ELEM(1, Seq)

#define GENERATE_COMMA() ,
#define GENERATE_SEMICOLON() ;
#define GENERATE_NOTHING()

#define FIRST_(r, GenSep, Pair) GenSep() FIRST(Pair)
#define SECOND_(r, GenSep, Pair) GenSep() SECOND(Pair)


#define MAP_FIRST(Fields, GenSep) \
    FIRST(HEAD(Fields)) EACH(FIRST_, GenSep, TAIL(Fields))

#define MAP_SECOND(Fields, GenSep) \
    SECOND(HEAD(Fields)) EACH(SECOND_, GenSep, TAIL(Fields))
    

#define GEN_CONSTRUCTOR_ARGUMENT(r, GenSep, Field) \
    GenSep() const FIRST(Field) & SECOND(Field)
    
#define GEN_CONSTRUCTOR_ARGUMENTS(Fields) \
    const FIRST(HEAD(Fields)) & SECOND(HEAD(Fields)) EACH(GEN_CONSTRUCTOR_ARGUMENT, GENERATE_COMMA, TAIL(Fields))

#define GEN_METHOD_(r, GenSep, Index, Field) \
    const FIRST(Field) & BOOST_PP_CAT(get_, SECOND(Field)) () const { return std::get< Index >(*this); }

#define GEN_METHODS(Fields) \
    BOOST_PP_SEQ_FOR_EACH_I(GEN_METHOD_, GENERATE_SEMICOLON, Fields)

#define GENERATE_MESSAGE(Name, Fields) \
    struct Name : std::tuple< MAP_FIRST(Fields, GENERATE_COMMA) > { \
        Name(GEN_CONSTRUCTOR_ARGUMENTS(Fields)) : \
                std::tuple< MAP_FIRST(Fields, GENERATE_COMMA) >(MAP_SECOND(Fields, GENERATE_COMMA)) {} \
        GEN_METHODS(Fields) \
    };


#include <iostream>
#include <tuple>

typedef int X;
typedef int Y;
typedef int Z;

GENERATE_MESSAGE(Point, ((X)(x))((Y)(y))((Z)(z)))
    
int main()
{
    Point p(1, 2, 3);
    std::cout << "Point: " << p.get_x() << ' ' << p.get_y() << ' ' << p.get_z(); 
}