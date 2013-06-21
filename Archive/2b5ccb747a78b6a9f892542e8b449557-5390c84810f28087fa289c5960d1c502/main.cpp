#include <iostream>
#include <vector>
#include <map>
#include <tuple>
#include <stdexcept>
#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <exception>
#include <unordered_set>
#include <unordered_map>
#include <cstdint>
#include <type_traits>
#include <typeinfo>
#include <limits>
        
 
 enum ETokenType
{
    // keywords
    KW_ALIGNAS,
    KW_ALIGNOF,
    KW_ASM,
    KW_AUTO,
    KW_BOOL,
    KW_BREAK,
    KW_CASE,
    KW_CATCH,
    KW_CHAR,
    KW_CHAR16_T,
	KW_CHAR32_T,
	KW_CLASS,
	KW_CONST,
	KW_CONSTEXPR,
	KW_CONST_CAST,
	KW_CONTINUE,
	KW_DECLTYPE,
	KW_DEFAULT,
	KW_DELETE,
	KW_DO,
	KW_DOUBLE,
	KW_DYNAMIC_CAST,
	KW_ELSE,
	KW_ENUM,
	KW_EXPLICIT,
	KW_EXPORT,
	KW_EXTERN,
	KW_FALSE,
	KW_FLOAT,
	KW_FOR,
	KW_FRIEND,
	KW_GOTO,
	KW_IF,
	KW_INLINE,
	KW_INT,
	KW_LONG,
	KW_MUTABLE,
	KW_NAMESPACE,
	KW_NEW,
	KW_NOEXCEPT,
	KW_NULLPTR,
	KW_OPERATOR,
	KW_PRIVATE,
	KW_PROTECTED,
	KW_PUBLIC,
	KW_REGISTER,
	KW_REINTERPET_CAST,
	KW_RETURN,
	KW_SHORT,
	KW_SIGNED,
	KW_SIZEOF,
	KW_STATIC,
	KW_STATIC_ASSERT,
	KW_STATIC_CAST,
	KW_STRUCT,
	KW_SWITCH,
	KW_TEMPLATE,
	KW_THIS,
	KW_THREAD_LOCAL,
	KW_THROW,
	KW_TRUE,
	KW_TRY,
	KW_TYPEDEF,
	KW_TYPEID,
	KW_TYPENAME,
	KW_UNION,
	KW_UNSIGNED,
	KW_USING,
	KW_VIRTUAL,
	KW_VOID,
	KW_VOLATILE,
	KW_WCHAR_T,
	KW_WHILE,

	// operators/punctuation
	OP_LBRACE,
	OP_RBRACE,
	OP_LSQUARE,
	OP_RSQUARE,
	OP_LPAREN,
	OP_RPAREN,
	OP_BOR,
	OP_XOR,
	OP_COMPL,
	OP_AMP,
	OP_LNOT,
	OP_SEMICOLON,
	OP_COLON,
	OP_DOTS,
	OP_QMARK,
	OP_COLON2,
	OP_DOT,
	OP_DOTSTAR,
	OP_PLUS,
	OP_MINUS,
	OP_STAR,
	OP_DIV,
	OP_MOD,
	OP_ASS,
	OP_LT,
	OP_GT,
	OP_PLUSASS,
	OP_MINUSASS,
	OP_STARASS,
	OP_DIVASS,
	OP_MODASS,
	OP_XORASS,
	OP_BANDASS,
	OP_BORASS,
	OP_LSHIFT,
	OP_RSHIFT,
	OP_RSHIFTASS,
	OP_LSHIFTASS,
	OP_EQ,
	OP_NE,
	OP_LE,
	OP_GE,
	OP_LAND,
	OP_LOR,
	OP_INC,
	OP_DEC,
	OP_COMMA,
	OP_ARROWSTAR,
	OP_ARROW,
};

std::unordered_map<std::string, ETokenType> StringToTokenTypeMap =
{
    // keywords
	{"alignas", KW_ALIGNAS},
	{"alignof", KW_ALIGNOF},
	{"asm", KW_ASM},
	{"auto", KW_AUTO},
	{"bool", KW_BOOL},
	{"break", KW_BREAK},
	{"case", KW_CASE},
	{"catch", KW_CATCH},
	{"char", KW_CHAR},
	{"char16_t", KW_CHAR16_T},
	{"char32_t", KW_CHAR32_T},
	{"class", KW_CLASS},
	{"const", KW_CONST},
	{"constexpr", KW_CONSTEXPR},
	{"const_cast", KW_CONST_CAST},
	{"continue", KW_CONTINUE},
	{"decltype", KW_DECLTYPE},
	{"default", KW_DEFAULT},
	{"delete", KW_DELETE},
	{"do", KW_DO},
	{"double", KW_DOUBLE},
	{"dynamic_cast", KW_DYNAMIC_CAST},
	{"else", KW_ELSE},
	{"enum", KW_ENUM},
	{"explicit", KW_EXPLICIT},
	{"export", KW_EXPORT},
	{"extern", KW_EXTERN},
	{"false", KW_FALSE},
	{"float", KW_FLOAT},
	{"for", KW_FOR},
	{"friend", KW_FRIEND},
	{"goto", KW_GOTO},
	{"if", KW_IF},
	{"inline", KW_INLINE},
	{"int", KW_INT},
	{"long", KW_LONG},
	{"mutable", KW_MUTABLE},
	{"namespace", KW_NAMESPACE},
	{"new", KW_NEW},
	{"noexcept", KW_NOEXCEPT},
	{"nullptr", KW_NULLPTR},
	{"operator", KW_OPERATOR},
	{"private", KW_PRIVATE},
	{"protected", KW_PROTECTED},
	{"public", KW_PUBLIC},
	{"register", KW_REGISTER},
	{"reinterpret_cast", KW_REINTERPET_CAST},
	{"return", KW_RETURN},
	{"short", KW_SHORT},
	{"signed", KW_SIGNED},
	{"sizeof", KW_SIZEOF},
	{"static", KW_STATIC},
	{"static_assert", KW_STATIC_ASSERT},
	{"static_cast", KW_STATIC_CAST},
	{"struct", KW_STRUCT},
	{"switch", KW_SWITCH},
	{"template", KW_TEMPLATE},
	{"this", KW_THIS},
	{"thread_local", KW_THREAD_LOCAL},
	{"throw", KW_THROW},
	{"true", KW_TRUE},
	{"try", KW_TRY},
	{"typedef", KW_TYPEDEF},
	{"typeid", KW_TYPEID},
	{"typename", KW_TYPENAME},
	{"union", KW_UNION},
	{"unsigned", KW_UNSIGNED},
	{"using", KW_USING},
	{"virtual", KW_VIRTUAL},
	{"void", KW_VOID},
	{"volatile", KW_VOLATILE},
	{"wchar_t", KW_WCHAR_T},
	{"while", KW_WHILE},

	// operators/punctuation
	{"{", OP_LBRACE},
	{"<%", OP_LBRACE},
	{"}", OP_RBRACE},
	{"%>", OP_RBRACE},
	{"[", OP_LSQUARE},
	{"<:", OP_LSQUARE},
	{"]", OP_RSQUARE},
	{":>", OP_RSQUARE},
	{"(", OP_LPAREN},
	{")", OP_RPAREN},
	{"|", OP_BOR},
	{"bitor", OP_BOR},
	{"^", OP_XOR},
	{"xor", OP_XOR},
	{"~", OP_COMPL},
	{"compl", OP_COMPL},
	{"&", OP_AMP},
	{"bitand", OP_AMP},
	{"!", OP_LNOT},
	{"not", OP_LNOT},
	{";", OP_SEMICOLON},
	{":", OP_COLON},
	{"...", OP_DOTS},
	{"?", OP_QMARK},
	{"::", OP_COLON2},
	{".", OP_DOT},
	{".*", OP_DOTSTAR},
	{"+", OP_PLUS},
	{"-", OP_MINUS},
	{"*", OP_STAR},
	{"/", OP_DIV},
	{"%", OP_MOD},
	{"=", OP_ASS},
	{"<", OP_LT},
	{">", OP_GT},
	{"+=", OP_PLUSASS},
	{"-=", OP_MINUSASS},
	{"*=", OP_STARASS},
	{"/=", OP_DIVASS},
	{"%=", OP_MODASS},
	{"^=", OP_XORASS},
	{"xor_eq", OP_XORASS},
	{"&=", OP_BANDASS},
	{"and_eq", OP_BANDASS},
	{"|=", OP_BORASS},
	{"or_eq", OP_BORASS},
	{"<<", OP_LSHIFT},
	{">>", OP_RSHIFT},
	{">>=", OP_RSHIFTASS},
	{"<<=", OP_LSHIFTASS},
	{"==", OP_EQ},
	{"!=", OP_NE},
	{"not_eq", OP_NE},
	{"<=", OP_LE},
	{">=", OP_GE},
	{"&&", OP_LAND},
	{"and", OP_LAND},
	{"||", OP_LOR},
	{"or", OP_LOR},
	{"++", OP_INC},
	{"--", OP_DEC},
	{",", OP_COMMA},
	{"->*", OP_ARROWSTAR},
	{"->", OP_ARROW}
};

 enum EFundamentalType
{
    // 3.9.1.2
	FT_SIGNED_CHAR,
	FT_SHORT_INT,
	FT_INT,
	FT_LONG_INT,
	FT_LONG_LONG_INT,

	// 3.9.1.3
	FT_UNSIGNED_CHAR,
	FT_UNSIGNED_SHORT_INT,
	FT_UNSIGNED_INT,
	FT_UNSIGNED_LONG_INT,
	FT_UNSIGNED_LONG_LONG_INT,

	// 3.9.1.1 / 3.9.1.5
	FT_WCHAR_T,
	FT_CHAR,
	FT_CHAR16_T,
	FT_CHAR32_T,

	// 3.9.1.6
	FT_BOOL,

	// 3.9.1.8
	FT_FLOAT,
	FT_DOUBLE,
	FT_LONG_DOUBLE,

	// 3.9.1.9
	FT_VOID,

	// 3.9.1.10
	FT_NULLPTR_T,

	FT_NA
};

// convert EFundamentalType to a source code
const std::map<EFundamentalType, std::string> FundamentalTypeToStringMap
{
	{FT_SIGNED_CHAR, "signed char"},
	{FT_SHORT_INT, "short int"},
	{FT_INT, "int"},
	{FT_LONG_INT, "long int"},
	{FT_LONG_LONG_INT, "long long int"},
	{FT_UNSIGNED_CHAR, "unsigned char"},
	{FT_UNSIGNED_SHORT_INT, "unsigned short int"},
	{FT_UNSIGNED_INT, "unsigned int"},
	{FT_UNSIGNED_LONG_INT, "unsigned long int"},
	{FT_UNSIGNED_LONG_LONG_INT, "unsigned long long int"},
	{FT_WCHAR_T, "wchar_t"},
	{FT_CHAR, "char"},
	{FT_CHAR16_T, "char16_t"},
	{FT_CHAR32_T, "char32_t"},
	{FT_BOOL, "bool"},
	{FT_FLOAT, "float"},
	{FT_DOUBLE, "double"},
	{FT_LONG_DOUBLE, "long double"},
	{FT_VOID, "void"},
	{FT_NULLPTR_T, "nullptr_t"}
};

const std::unordered_set<int> integralTypesSet
{
    FT_SIGNED_CHAR, FT_SHORT_INT, FT_INT, FT_LONG_INT, FT_LONG_LONG_INT, FT_UNSIGNED_CHAR, FT_UNSIGNED_SHORT_INT, FT_UNSIGNED_INT, 
	FT_UNSIGNED_LONG_INT, FT_UNSIGNED_LONG_LONG_INT, FT_WCHAR_T, FT_CHAR, FT_CHAR16_T, FT_CHAR32_T, FT_BOOL, 
} ;

const std::unordered_set<int> integralSignedTypesSet
{
    FT_SIGNED_CHAR, FT_SHORT_INT, FT_INT, FT_LONG_INT, FT_LONG_LONG_INT, FT_WCHAR_T,  FT_BOOL, //FT_CHAR,
} ;


bool isUnsignedType( int t )
{
    return ( integralSignedTypesSet.count( t ) == 0 ) ;
}

bool isTokenOperator( ETokenType token )
{
    return ( token >= OP_LBRACE ) ;
}

enum EPostTokenDataType
{
  EPT_SIMPLE,
  EPT_IDENTIFIER,
  EPT_TYPE,
};

bool PA3Mock_IsDefinedIdentifier(const std::string& identifier)
{
        if (identifier.empty())
                return false;
        else
                return identifier[0] % 2;
}

bool voidPtrToBool( void * src )
{
        return static_cast<bool>( *static_cast<unsigned int*>( src ) ) ;
}

void releaseData( void *&dest )
{
    if( nullptr != dest )
    {
        uintmax_t *p = static_cast<uintmax_t*>( dest ) ;
        
        delete p ;
    }
}

void replaceData( uintmax_t results, void *&data )
{
    releaseData( data ) ;
    
    uintmax_t *ptr = new uintmax_t ;
    
    *ptr = results;
    
    data =  ptr ;
}

void replaceDataVoid( void *src, void *&dest )
{
    releaseData( dest ) ;
    
    uintmax_t *ptr = new uintmax_t ;
    
    *ptr = *static_cast<uintmax_t*>(src);
    
    dest = ptr ;
    std::cout << std::hex << "src: " << src << " dest: " << dest << std::endl; 
}

struct PostTokenData
{
    EPostTokenDataType
        eptDataType ;
    EFundamentalType
        type ;
    std::string
        sourceOrId,
        UDSuffix,
        lPrefix ;
    void
        *data ;
    size_t
        nBytes ;
    bool
        isArray ;
        
    PostTokenData( std::string src, std::string suffix, std::string prefix, EPostTokenDataType eptT, EFundamentalType t, const void *d, size_t bytes, bool isArr ) :
        eptDataType( eptT ), type( t ), sourceOrId( src ), UDSuffix( suffix ), lPrefix( prefix ),  nBytes( bytes ), isArray( isArr )
    {
        const void *dp = d ;
        uintmax_t x = 0 ;
        
        if( "true" == src || "false" == src )
        {
            if( "true" == src )
            {
    	sourceOrId = "1" ;
                x = 1 ;
            }
	    else
	    {
		sourceOrId = "0" ;
	    }
            
            dp = &x ;
            nBytes = sizeof( uintmax_t ) ;
            type = FT_INT ;
	    eptDataType = EPT_TYPE ;
            isArray = false ;
        }
        
        if( nBytes > 0 )
        {
            data    = new char[nBytes] ;
            std::memcpy( data, dp, nBytes ) ;
        }
        
        std::cout << "FT_INT: " << FT_INT << " usi: " << FT_UNSIGNED_LONG_INT << " PDT Type: " << type << std::endl ; 
    }
    
    unsigned int getUnsignedInt()
    {
        return static_cast<unsigned int>( *static_cast<unsigned int*>( data ) ) ;
    }
} ;

bool isValidPeek( std::vector<PostTokenData> &ptd, size_t index, size_t endPos )
{    
    if( index < endPos )
    {
        return  true ;
    }
    
    return false ;
}

bool isOp( std::vector<PostTokenData> &ptd, size_t index, ETokenType opToken )
{
    if( EPT_SIMPLE == ptd[index].eptDataType && StringToTokenTypeMap[ptd[index].sourceOrId] == opToken )
    {
        return true ;
    }
    
    return false ;
}

ETokenType getOp( std::vector<PostTokenData> &ptd, size_t index )
{
    return StringToTokenTypeMap[ptd[index].sourceOrId] ;
}


bool isArray( std::vector<PostTokenData> &ptd, size_t currPos  )
{
    if( ptd[currPos].isArray )
    {
        return true ;
    }
    
    return false ;
}

bool isIntegralType( std::vector<PostTokenData> &ptd, size_t currPos  )
{
    if( integralTypesSet.count( ptd[currPos].type ) == 0 )
    {
        return true ;
    }
    return false ;
}

bool hasType( std::vector<PostTokenData> &ptd, size_t currPos  )
{
    if( EPT_TYPE == ptd[currPos].eptDataType )
    {
        return true ;
    }
    return false ;
}

bool hasIdentifier( std::vector<PostTokenData> &ptd, size_t currPos  )
{
    if( EPT_IDENTIFIER == ptd[currPos].eptDataType )
    {
        return true ;
    }
    return false ;
}


template <typename T1>
EFundamentalType callOp( void *v1, void *v2, EFundamentalType et1, EFundamentalType et2, T1 &result, ETokenType op )
{
    if( et1 == FT_LONG_INT && et2 == FT_LONG_INT )
    {
        return doOp( *static_cast<intmax_t*>( v1 ), *static_cast<intmax_t*>( v2 ), result, op, true, false ) ;
    }
    else if( et1 == FT_UNSIGNED_LONG_INT && et2 == FT_UNSIGNED_LONG_INT )
    {
        return doOp( *static_cast<uintmax_t*>( v1 ), *static_cast<uintmax_t*>( v2 ), result, op, false, false ) ;
    }
    else if( et1 == FT_LONG_INT && et2 == FT_UNSIGNED_LONG_INT )
    {
        return doOp( *static_cast<uintmax_t*>( v1 ), *static_cast<uintmax_t*>( v2 ), result, op, false, false ) ;
    }
    else if( et1 == FT_UNSIGNED_LONG_INT && et2 == FT_LONG_INT )
    {
        return doOp( *static_cast<uintmax_t*>( v1 ), *static_cast<uintmax_t*>( v2 ), result, op, false, false ) ;
    }
    else if( et2 == FT_NA )
    {
	if( et1 == FT_UNSIGNED_LONG_INT )
	{
        	return doOp( *static_cast<uintmax_t*>( v1 ), 0, result, op, false, true ) ;
	}
	else
	{
        	return doOp( *static_cast<intmax_t*>( v1 ), 0, result, op, true, true ) ;
	}
    }
}
      
template <typename T1, typename T2, typename T3 >
EFundamentalType doOp( T1 t1, T2 t2, T3 &result, ETokenType op, bool comboSigned, bool isUnary )
{    
    EFundamentalType type ;
    bool isSigned = comboSigned ;
    bool overflow1 = false;
    std::cout << "type T1: " << typeid(t1).name() << " type T2: " << typeid(t2).name() << std::endl ;
    unsigned long long temp ;
    
    if( OP_PLUS == op )
    {
    	if( isUnary )
    	{
            	temp = +t1 ;
    	}
    	else
    	{
                if( comboSigned )
                {
                    if( (static_cast<intmax_t>(t2) > 0 && (static_cast<intmax_t>(t1) > ( std::numeric_limits<intmax_t>::max() - static_cast<intmax_t>(t2) ) ) ) ||
                        ( static_cast<intmax_t>(t2) < 0 && (static_cast<intmax_t>(t1) < ( std::numeric_limits<intmax_t>::min() - static_cast<intmax_t>(t2)) ) ) )
                    {
                               overflow1 = true ;
                    }
                }
            	temp = t1 + t2 ;
    	}
    }
    else if( OP_MINUS == op )
    {
    	if( isUnary )
    	{
            	temp = -t1 ;
    	}
    	else
    	{
            if( comboSigned )
                {
                    if( ( static_cast<intmax_t>(t2) > 0 && (static_cast<intmax_t>(t1) < ( std::numeric_limits<intmax_t>::min() + static_cast<intmax_t>(t2) ) )) ||
                        ( static_cast<intmax_t>(t2) < 0 && (static_cast<intmax_t>(t1) > ( std::numeric_limits<intmax_t>::max() + static_cast<intmax_t>(t2)) ) ) )
                    {
                               overflow1 = true ;
                    }
                }
            	
                temp = t1 - t2 ;
    	}
    }
    else if( OP_LNOT == op )
    {
        temp = !t1 ;
    }
    else if( OP_COMPL == op )
    {
        temp = ~t1 ;
    }
    else if( OP_STAR  == op )
    {
        if( comboSigned )
        {
            if( t1 > 0 )
            {
                if( t2 > 0 )
                {
                    if (static_cast<intmax_t>(t1) > (std::numeric_limits<intmax_t>::max() / static_cast<intmax_t>(t2) ) )
                    {
                        overflow1 = true ;
                    }
                } else {
                    if (static_cast<intmax_t>(t2) < (std::numeric_limits<intmax_t>::min() / static_cast<intmax_t>(t1) ) )
                    {
                        overflow1 = true ;
                    }
                }
            }
            else
            {
                if( t2 > 0 )
                {
                    if (static_cast<intmax_t>(t1) < (std::numeric_limits<intmax_t>::min() / static_cast<intmax_t>(t2) ) )
                    {
                        overflow1 = true ;
                    }
                } else {
                    if ( static_cast<intmax_t>(t1) != 0 && (static_cast<intmax_t>(t2) < (std::numeric_limits<intmax_t>::max() / static_cast<intmax_t>(t1) )) )
                    {
                        overflow1 = true ;
                    }
                }
            }
        }
        
       	temp = t1 * t2 ;
    }
    else if( OP_DIV == op )
    {
        if( 0 == t2 )
        {
            throw std::logic_error("Divide by zero") ;
        }
        
        if( comboSigned )
                {
                    if( (static_cast<intmax_t>(t2) == 0) || (static_cast<intmax_t>(t1) == ( std::numeric_limits<intmax_t>::min() && ( static_cast<intmax_t>(t2) == -1) ) ) )
                    {
                        overflow1 = true ;
                    }
                }
                
       	temp = t1 / t2 ;
    }
    else if( OP_MOD == op )
    {
        if( 0 == t2 )
        {
            throw std::logic_error("Mod by zero") ;
        }
        
        if( comboSigned )
                {
                    if( (static_cast<intmax_t>(t2) == 0) || (static_cast<intmax_t>(t1) == ( std::numeric_limits<intmax_t>::min() && ( static_cast<intmax_t>(t2) == -1) ) ) )
                    {
                        overflow1 = true ;
                    }
                }

       	temp = t1 % t2 ;
    }
    else if( OP_LSHIFT == op )
    {
        if( comboSigned )
        {
    		if( static_cast<intmax_t>(t2) < 0 )
		{
            		throw std::logic_error("Shift by negative number") ;
		}
    		else if( static_cast<uintmax_t>(t2) >= (sizeof(t1)-1) )
		{
            		throw std::logic_error("Shift by size or greater of data type") ;
		}
	    }
   	  else if( static_cast<uintmax_t>(t2) >= sizeof(t1) )
	  {
           	throw std::logic_error("Shift by size or greater of data type") ;
	  }

	temp = t1 << t2 ;
    }
    else if( OP_RSHIFT == op )
    {
        if( comboSigned )
        {
    		if( static_cast<intmax_t>(t2) < 0 )
		{
            		throw std::logic_error("Shift by negative number") ;
		}
    		else if( static_cast<uintmax_t>(t2) >= (sizeof(t1)-1) )
		{
            		throw std::logic_error("Shift by size or greater of data type") ;
		}
	}
	else if( static_cast<uintmax_t>(t2) >= sizeof(t1) )
	{
           	throw std::logic_error("Shift by size or greater of data type") ;
	}

	temp = t1 >> t2 ;
    }

    std::cout <<  static_cast<long long>(temp) << std::endl ;
    std::cout << std::numeric_limits<intmax_t>::max() << std::endl ;
    std::cout << std::numeric_limits<intmax_t>::min() << std::endl ;
    
    if( overflow1 )
    {
            std::cout << "Signed overflow Promoting to unsigned" << std::endl ;        
            isSigned = false ;
    }
    
    if( comboSigned )
    {
        if( static_cast<long long>( temp ) > std::numeric_limits<intmax_t>::max() ||
            static_cast<long long>( temp )  < std::numeric_limits<intmax_t>::min() )
        {
            std::cout << "Promoting to unsigned" << std::endl ;        
            isSigned = false ;
        }
    }
    
    if( temp > std::numeric_limits<uintmax_t>::max() )
    {
        std::cout << "Overflow! temp is outside the range of uintmax_t" << std::endl ;
        std::cout << temp << std::endl ;
        std::cout << std::numeric_limits<uintmax_t>::max() << std::endl ;
    }
    
    if( isSigned )
    {
        std::cout << "Is Signed!" << std::endl ;
        type = FT_LONG_INT ;
    }
    else
    {
        type = FT_UNSIGNED_LONG_INT ;
    }
    
    result = temp ;
    
    return type ;
}

class ExprAST
{
     public:
    ExprAST() : data(nullptr){}
	virtual ~ExprAST() {} ;

	virtual void eval() = 0 ;
	virtual EFundamentalType evalType() { return type ; }  ;

        void
            *data ;
        EFundamentalType
            type ;
        ETokenType
            op ;
	virtual void *getData() { return data ; } ;

	virtual void copyData( ExprAST *ea )
	{
                replaceDataVoid( ea->getData(), data ) ;
		type	= ea->type ;
	}
};

class primaryExprAST ;

class unaryExprAST : public ExprAST
{
    public:
        unaryExprAST() : PrimaryExpr(nullptr), UnaryExpr(nullptr) {}
        virtual ~unaryExprAST()  {} 
        virtual void eval()
	{
            if( UnaryExpr )
            {
        		std::cout << "unaryExprAST -> eval -> " << std::endl ;
                        uintmax_t result ;
                        UnaryExpr->eval() ;
        
        		std::cout << "OP: " << op <<  std::endl ;
                std::cout << ( OP_PLUS == op  ? " OP_PLUS " : ( OP_MINUS == op ? "OP_MINUS" : ( OP_LNOT == op ? "OP_LNOT" : " OP_COMPL " ) ) ) ;
                	if( UnaryExpr->type == FT_LONG_INT )
            		{
        			std::cout << *static_cast<intmax_t*>( UnaryExpr->data ) ;
				//type = FT_LONG_INT ;
        		}
        		else
        		{
        			std::cout << *static_cast<uintmax_t*>( UnaryExpr->data ) ;
				//type = FT_UNSIGNED_LONG_INT ;
        		}
        		std::cout << std::endl ;
        
        		type = callOp(  UnaryExpr->data , nullptr, UnaryExpr->type, FT_NA, result, op ) ;
        		std::cout << "result = " << result << std::endl ;
        	    replaceData( result, data ) ;
            }
            else if( PrimaryExpr )
            {
		    std::cout << "unaryExprAST -> eval -> PrimaryExpr" << std::endl ;
                PrimaryExpr->eval() ;
                copyData( PrimaryExpr ) ;
		 //std::cout << "done Copy" << std::endl ;
            }
	}

	virtual EFundamentalType evalType()
	{
		if( UnaryExpr )
		{
			return UnaryExpr->evalType() ;
		}
		else
		{
			return PrimaryExpr->evalType() ;
		}
	} 
        
        void setUnary( unaryExprAST *eun )
        {
            UnaryExpr = eun ;
        }
        
        //void setPrimary( primaryExprAST *epri )
        void setPrimary( ExprAST *epri )
        {
            PrimaryExpr = epri ;
        }

    private:
        ExprAST
            *PrimaryExpr ;
        unaryExprAST
            *UnaryExpr ;
} ;

class multiplicativeExprAST : public ExprAST
{
    public:
        multiplicativeExprAST() : UnaryExpr(nullptr), MultiplicativeExpr(nullptr) {}
        virtual ~multiplicativeExprAST()  {} 
        virtual void eval()
	{
            if( UnaryExpr && MultiplicativeExpr )
            {
                MultiplicativeExpr->eval() ;
                
                uintmax_t result = *static_cast<uintmax_t*>( MultiplicativeExpr->data ) ;

                UnaryExpr->eval() ;

		std::cout << "OP" << std::endl ;
		if( MultiplicativeExpr->type == FT_LONG_INT )
		{
			std::cout << *static_cast<intmax_t*>( MultiplicativeExpr->data ) ;
		}
		else
		{
			std::cout << *static_cast<uintmax_t*>( MultiplicativeExpr->data ) ;
		}
                std::cout << ( OP_STAR == op  ? " OP_STAR " : ( OP_DIV == op ? "OP_DIV" : " OP_MOD " ) ) ;
		if( UnaryExpr->type == FT_LONG_INT )
		{
			std::cout << *static_cast<intmax_t*>( UnaryExpr->data ) ;
		}
		else
		{
			std::cout << *static_cast<uintmax_t*>( UnaryExpr->data ) ;
		}
		std::cout << std::endl ;

		type = callOp(  MultiplicativeExpr->data , UnaryExpr->data, MultiplicativeExpr->type, UnaryExpr->type, result, op ) ;
		std::cout << "result = " << result << std::endl ;

                replaceData( result, data ) ;
            }
            else if( UnaryExpr )
            {
		    std::cout << "multiplicativeExprAST -> eval -> UnaryExpr" << std::endl ;
                UnaryExpr->eval() ;
                copyData( UnaryExpr ) ;
		//std::cout << "done Unaray to Mult Copy" << std::endl ;
            }
	}

	virtual EFundamentalType evalType()
	{
		 std::cout << "multiplicativeExprAST -> evalType " << std::endl ;
		if( MultiplicativeExpr )
		{
			if( isUnsignedType( MultiplicativeExpr->evalType() ) || isUnsignedType( UnaryExpr->evalType() ) )
			{
				std::cout << "Promote to unsigned" << std::endl ;
				type = FT_UNSIGNED_LONG_INT ;
			}
		}
		else
		{
			return UnaryExpr->evalType() ;
		}

		return type ;
	}  ;
        
        
        //void setMul( multiplicativeExprAST *emul )
        void setMul( ExprAST *emul )
        {
            MultiplicativeExpr = emul ;
        }
        
        void setUnary( unaryExprAST *eun )
        {
            UnaryExpr = eun ;
        }

    private:
        
        unaryExprAST
            *UnaryExpr ;
        //multiplicativeExprAST
        ExprAST
            *MultiplicativeExpr ;
} ;

class additiveExprAST : public ExprAST
{
    public:
        additiveExprAST() : MultiplicativeExpr(nullptr), AdditiveExpr(nullptr) {}
        virtual ~additiveExprAST()  {} 
        virtual void eval()
	{
            if( MultiplicativeExpr && AdditiveExpr )
            {
		    std::cout << "additiveExprAST -> eval -> ... " ;
                AdditiveExpr->eval() ;
                
                uintmax_t result = *static_cast<uintmax_t*>( AdditiveExpr->data ) ;

                MultiplicativeExpr->eval() ;

		std::cout << "OP" << std::endl ;
		if( AdditiveExpr->type == FT_LONG_INT )
		{
			std::cout << *static_cast<intmax_t*>( AdditiveExpr->data ) ;
		}
		else
		{
			std::cout << *static_cast<uintmax_t*>( AdditiveExpr->data ) ;
		}
                std::cout << ( OP_PLUS == op  ? " OP_PLUS " : " OP_MINUS " ) ;
		if( MultiplicativeExpr->type == FT_LONG_INT )
		{
			std::cout << *static_cast<intmax_t*>( MultiplicativeExpr->data ) ;
		}
		else
		{
			std::cout << *static_cast<uintmax_t*>( MultiplicativeExpr->data ) ;
		}
		std::cout << std::endl ;

		type = callOp(  AdditiveExpr->data , MultiplicativeExpr->data, AdditiveExpr->type, MultiplicativeExpr->type, result, op ) ;
		std::cout << "result = " << result << std::endl ;

                replaceData( result, data ) ;
		std::cout << "done replace" << std::endl ;
            }
            else if( MultiplicativeExpr )
            {
		    std::cout << "additiveExprAST -> eval -> MultiplicativeExpr" << std::endl ;
                MultiplicativeExpr->eval() ;
                copyData( MultiplicativeExpr ) ;
            }
	}

	virtual EFundamentalType evalType()
	{
		std::cout << " additiveExprAST -> evalType " << std::endl ;
		if( AdditiveExpr )
		{
			if( isUnsignedType( MultiplicativeExpr->evalType() ) || isUnsignedType( AdditiveExpr->evalType() ) )
			{
				std::cout << "Promote to unsigned" << std::endl ;
				type = FT_UNSIGNED_LONG_INT ;
			}
		}
		else
		{
			return MultiplicativeExpr->evalType() ;
		}

		return type ;
	}  ;
        
        void setAdditive( ExprAST *eadditive )
        {
            AdditiveExpr = eadditive ;
        }
        
        void setMul( multiplicativeExprAST *emul )
        {
            MultiplicativeExpr = emul ;
        }

    private:
        multiplicativeExprAST
            *MultiplicativeExpr ;
       ExprAST 
            *AdditiveExpr ;
} ;

class shiftExprAST : public ExprAST
{
    public:
        shiftExprAST() : AdditiveExpr(nullptr), ShiftExpr(nullptr) {}
        virtual ~shiftExprAST()  {} 
        virtual void eval()
	{
            if( AdditiveExpr && ShiftExpr )
            {
                ShiftExpr->eval() ;
                
                uintmax_t result = *static_cast<uintmax_t*>( ShiftExpr->data ) ;

                AdditiveExpr->eval() ;

		std::cout << "OP" << std::endl ;
		if( ShiftExpr->type == FT_LONG_INT )
		{
			std::cout << *static_cast<intmax_t*>( ShiftExpr->data ) ;
		}
		else
		{
			std::cout << *static_cast<uintmax_t*>( ShiftExpr->data ) ;
		}
                std::cout << ( OP_LSHIFT == op  ? " << " : " >> " ) ;
		if( AdditiveExpr->type == FT_LONG_INT )
		{
			std::cout << *static_cast<intmax_t*>( AdditiveExpr->data ) ;
		}
		else
		{
			std::cout << *static_cast<uintmax_t*>( AdditiveExpr->data ) ;
		}
		std::cout << std::endl ;

		type = callOp(  ShiftExpr->data, AdditiveExpr->data, ShiftExpr->type, AdditiveExpr->type, result, op ) ;
		std::cout << "result = " << result << std::endl ;

                replaceData( result, data ) ;
            }
            else if( AdditiveExpr )
            {
		    std::cout << "shiftExprAST -> eval -> AdditiveExpr" << std::endl ;
                AdditiveExpr->eval() ;
                copyData( AdditiveExpr ) ;
            }
	}

	virtual EFundamentalType evalType()
	{
		if( ShiftExpr )
		{
			return type ;
		}
		else
		{
			return AdditiveExpr->evalType() ;
		}
	} 
        
        void setShift( ExprAST *eshift )
        {
            ShiftExpr = eshift ;
        }
        
        void setAdditive( additiveExprAST *eadditive )
        {
            AdditiveExpr = eadditive ;
        }

    private:
        
        additiveExprAST
            *AdditiveExpr ;
        ExprAST
            *ShiftExpr ;
} ;

class relationalExprAST : public ExprAST
{
    public:
        relationalExprAST() : ShiftExpr(nullptr), RelationalExpr(nullptr) {}
        virtual ~relationalExprAST()  {} 
        virtual void eval()
	{
            if( ShiftExpr && RelationalExpr )
            {
                RelationalExpr->eval() ;
                
                uintmax_t result = *static_cast<uintmax_t*>( RelationalExpr->data ) ;

                ShiftExpr->eval() ;

		if( OP_GT == op )
		{
			bool comp = ( result > *static_cast<uintmax_t*>( ShiftExpr->data ) );

                	result = static_cast<uintmax_t>( comp ) ;
		}
		else if( OP_LT == op )
		{
			bool comp = ( result < *static_cast<uintmax_t*>( ShiftExpr->data ) );

                	result = static_cast<uintmax_t>( comp ) ;
		}
		else if( OP_GE == op )
		{
			bool comp = ( result >= *static_cast<uintmax_t*>( ShiftExpr->data ) );

                	result = static_cast<uintmax_t>( comp ) ;
		}
		else if( OP_LE == op )
		{
			bool comp = ( result <= *static_cast<uintmax_t*>( ShiftExpr->data ) );

                	result = static_cast<uintmax_t>( comp ) ;
		}

                replaceData( result, data ) ;
            }
            else if( ShiftExpr )
            {
		        std::cout << "relationalExprAST -> eval -> ShiftExpr" << std::endl ;
                ShiftExpr->eval() ;
                copyData( ShiftExpr ) ;
            }
	}

	virtual EFundamentalType evalType()
	{
		if( RelationalExpr )
		{
			return type ;
		}
		else
		{
			return ShiftExpr->evalType() ;
		}
	} 
        
        void setRelational( ExprAST *erelational )
        {
            RelationalExpr = erelational ;
        }
        
        void setShift( shiftExprAST *eshift )
        {
            ShiftExpr = eshift ;
        }
        
    private:
        
        shiftExprAST
            *ShiftExpr ;
        ExprAST
            *RelationalExpr ;
} ;

class equalityExprAST : public ExprAST
{
    public:
        equalityExprAST() : RelationalExpr(nullptr), EqualityExpr(nullptr) {}
        virtual ~equalityExprAST()  {} 
        virtual void eval()
        {
            if( RelationalExpr && EqualityExpr )
            {
                EqualityExpr->eval() ;
                
                uintmax_t result = *static_cast<uintmax_t*>( EqualityExpr->data ) ;

                RelationalExpr->eval() ;

		if( OP_EQ == op )
		{
			bool comp = ( result == *static_cast<uintmax_t*>( RelationalExpr->data ) );

                	result = static_cast<uintmax_t>( comp ) ;
		}
		else if( OP_NE == op )
		{
			bool comp = ( result != *static_cast<uintmax_t*>( RelationalExpr->data ) );

                	result = static_cast<uintmax_t>( comp ) ;
		}

                replaceData( result, data ) ;
            }
            else if( RelationalExpr )
            {
		    std::cout << "equalityExprAST -> eval -> RelationalExpr" << std::endl ;
                RelationalExpr->eval() ;
                copyData( RelationalExpr ) ;
		std::cout << "equalityExprAST -> eval -> RelationalExpr Done" << std::endl ;
            }
        }

	virtual EFundamentalType evalType()
	{
		if( EqualityExpr )
		{
			return type ;
		}
		else
		{
			return RelationalExpr->evalType() ;
		}
	} 
        
        void setEquality( equalityExprAST *eequality )
        {
            EqualityExpr = eequality ;
        }
        
        void setRelational( relationalExprAST *erelational )
        {
            RelationalExpr = erelational ;
        }
        
    private:
        
        relationalExprAST
            *RelationalExpr ;
        equalityExprAST
            *EqualityExpr ;
} ;

class andExprAST : public ExprAST
{
    public:
        andExprAST() : EqualityExpr(nullptr), AndExpr(nullptr) {}
        virtual ~andExprAST()  {} 
        virtual void eval()
        {
            if( EqualityExpr && AndExpr )
            {
                AndExpr->eval() ;
                
                uintmax_t result = *static_cast<uintmax_t*>( AndExpr->data ) ;
                
                EqualityExpr->eval() ;
                
                result &= *static_cast<uintmax_t*>( EqualityExpr->data ) ;
                
                replaceData( result, data ) ;
            }
            else if( EqualityExpr )
            {
		    std::cout << "andExprAST -> eval -> EqualityExpr" << std::endl ;
                EqualityExpr->eval() ;
                copyData( EqualityExpr ) ;
		std::cout << "andExprAST -> eval -> EqualityExpr Done " << std::endl ;
            }
        }

	virtual EFundamentalType evalType()
	{
		if( AndExpr )
		{
			return type ;
		}
		else
		{
			return EqualityExpr->evalType() ;
		}
	} 
        
        void setAnd( andExprAST *eand )
        {
            AndExpr = eand ;
        }
        
        void setEquality( equalityExprAST *eequality )
        {
            EqualityExpr = eequality ;
        }
        
    private:
        equalityExprAST
            *EqualityExpr ;
        andExprAST
            *AndExpr ;
        
} ;

class exclusiveOrExprAST : public ExprAST
{
    public:
        exclusiveOrExprAST() : ExclusiveOrExpr(nullptr), AndExpr(nullptr) {}
        virtual ~exclusiveOrExprAST()  {} 
        virtual void eval()
        {
            if( ExclusiveOrExpr && AndExpr )
            {
                ExclusiveOrExpr->eval() ;
                
                uintmax_t result = *static_cast<uintmax_t*>( ExclusiveOrExpr->data ) ;
                
                AndExpr->eval() ;
                
                result ^= *static_cast<uintmax_t*>( AndExpr->data ) ;
                
                replaceData( result, data ) ;
            }
            else if( AndExpr )
            {
		    std::cout << "exclusiveOrExprAST -> eval -> AndExpr" << std::endl ;
                AndExpr->eval() ;
                copyData( AndExpr ) ;
		std::cout << "exclusiveOrExprAST -> eval -> AndExpr done" << std::endl ;
            }
        }

	virtual EFundamentalType evalType()
	{
		if( ExclusiveOrExpr )
		{
			return type ;
		}
		else
		{
			return AndExpr->evalType() ;
		}
	} 
        
        void setExclusiveOr( exclusiveOrExprAST *exor )
        {
            ExclusiveOrExpr = exor ;
        }
        
        void setAnd( andExprAST *eand )
        {
            AndExpr = eand ;
        }
        
    private:
        exclusiveOrExprAST
            *ExclusiveOrExpr ;
        andExprAST
            *AndExpr ;
} ;

class inclusiveOrExprAST : public ExprAST
{
    public:
        inclusiveOrExprAST() : InclusiveOrExpr(nullptr), ExclusiveOrExpr(nullptr) {}
        virtual ~inclusiveOrExprAST()  {} 
        virtual void eval()
        {
            if( InclusiveOrExpr && ExclusiveOrExpr )
            {
                InclusiveOrExpr->eval() ;
                
                uintmax_t result = *static_cast<uintmax_t*>( InclusiveOrExpr->data ) ;
                
                ExclusiveOrExpr->eval() ;
                
                result |= *static_cast<uintmax_t*>( ExclusiveOrExpr->data ) ;
                
                replaceData( result, data ) ;
            }
            else if( ExclusiveOrExpr )
            {
		    std::cout << "inclusiveOrExprAST -> eval -> ExclusiveOrExpr" << std::endl ;
                ExclusiveOrExpr->eval() ;
                copyData( ExclusiveOrExpr ) ;
		std::cout << "inclusiveOrExprAST -> eval -> ExclusiveOrExpr done " << std::endl ;
            }
        }

	virtual EFundamentalType evalType()
	{
		if( InclusiveOrExpr )
		{
			return type ;
		}
		else
		{
			return ExclusiveOrExpr->evalType() ;
		}
	} 
        
        void setInclusiveOr( inclusiveOrExprAST *ior )
        {
            InclusiveOrExpr = ior ;
        }
        
        void setExclusiveOr( exclusiveOrExprAST *exor )
        {
            ExclusiveOrExpr = exor ;
        }
        
        bool dataAsBool() { return voidPtrToBool( data ) ; } ;
        
    private:
        inclusiveOrExprAST
            *InclusiveOrExpr ;
        exclusiveOrExprAST
            *ExclusiveOrExpr ;
} ;

class logicalAndExprAST : public ExprAST
{
    public:
        logicalAndExprAST() : LogicalAndExpr(nullptr), InclusiveOrExpr(nullptr) {}
        virtual ~logicalAndExprAST()  {} 
        virtual void eval()
        {
            if( LogicalAndExpr && InclusiveOrExpr )
            {
		    std::cout << "logicalAndExprAST -> eval -> " << std::endl ;
		    std::cout  << "orig data: " << std::hex << LogicalAndExpr->data << std::endl ;
                LogicalAndExpr->eval() ;
                
		std::cout  << "cast: " << std::hex << *static_cast<uintmax_t*>( LogicalAndExpr->data )<< std::endl ;
                uintmax_t result = *static_cast<uintmax_t*>( LogicalAndExpr->data ) ;
                
                std::cout << result << " && " ;
                if( result )
                {
                    InclusiveOrExpr->eval() ;
                    
                    std::cout << *static_cast<uintmax_t*>( InclusiveOrExpr->data ) << std::endl ;
                    
                    result = *static_cast<uintmax_t*>( InclusiveOrExpr->data ) ;

		   if( result )
		    {
			    result = 1 ;
		    }
                
                    replaceData( result, data ) ;
                }
                else
                {
                    result = 0 ;
                    
                    //std::cout << 0 << " && " << *static_cast<uintmax_t*>( InclusiveOrExpr->data ) << std::endl ;
                    
                    replaceData( result, data ) ;
                }
            }
            else if( InclusiveOrExpr )
            {
		        std::cout << "logicalAndExprAST -> eval -> InclusiveOrExpr" << std::endl ;
                InclusiveOrExpr->eval() ;
                copyData( InclusiveOrExpr ) ;
		std::cout << "logicalAndExprAST -> eval -> InclusiveOrExpr done" << std::endl ;
            }
        }

	virtual EFundamentalType evalType()
	{
		std::cout << "logicalAnd evalType -> " << std::endl ;
		if( LogicalAndExpr )
		{
			return type ;
		}
		else
		{
			return InclusiveOrExpr->evalType() ;
		}
	} 
        
        void setLogicalAnd( ExprAST *land )
        {
            LogicalAndExpr = land ;
        }
        
        void setInclusiveOr( inclusiveOrExprAST *ior )
        {
            InclusiveOrExpr = ior ;
        }
        
    private:
        ExprAST
            *LogicalAndExpr ;
        inclusiveOrExprAST
            *InclusiveOrExpr ;
} ;


class logicalOrExprAST : public ExprAST
{
    public:
        logicalOrExprAST() : LogicalOrExpr(nullptr), LogicalAndExpr(nullptr)  {}
        virtual ~logicalOrExprAST()  {} 
        virtual void eval()
        {
            if( LogicalAndExpr && LogicalOrExpr )
            {
                LogicalOrExpr->eval() ;
                
                uintmax_t result = *static_cast<uintmax_t*>( LogicalOrExpr->data ) ;
                
                if( !result )
                {
                    LogicalAndExpr->eval() ;
                
                    std::cout << result << " || " << *static_cast<uintmax_t*>( LogicalAndExpr->data ) << std::endl ;
		    result = 1 ;
                
                    result =  result || *static_cast<uintmax_t*>( LogicalAndExpr->data ) ;
                }
                else
                {
                    std::cout << result << " || " << 0 << std::endl ;
		    if( result )
		    {
			    result = 1 ;
		    }
                }
                
                replaceData( result, data ) ;
            }
            else if( LogicalAndExpr )
            {
		    std::cout << "logicalOrExprAST -> eval -> LogicalAndExpr" << std::endl ;
                LogicalAndExpr->eval() ;
                copyData( LogicalAndExpr ) ;
		std::cout << "logicalOrExprAST -> eval -> LogicalAndExpr done" << std::endl ;
            }
        }

	virtual EFundamentalType evalType()
	{
		std::cout << "logicalOr evalType -> " << std::endl ;
		if( LogicalOrExpr )
		{
			return type ;
		}
		else
		{
			return LogicalAndExpr->evalType() ;
		}
	} 
        
        void setLogicalOr( ExprAST *lor )
        {
            LogicalOrExpr = lor ;
        }
        
        void setLogicalAnd( logicalAndExprAST *land )
        {
            LogicalAndExpr = land ;
        }
        
    private:
        ExprAST
            *LogicalOrExpr ;
        logicalAndExprAST
            *LogicalAndExpr ;
} ;

class controllingExprAST : public ExprAST
{
    public:
        controllingExprAST() : LogicalOrExpr(nullptr), LControllingExpr(nullptr), RControllingExpr(nullptr) {} 
        virtual ~controllingExprAST()  {} 
        virtual void eval()
        {
            if( LControllingExpr && RControllingExpr && LogicalOrExpr )
            {
                LogicalOrExpr->eval() ;
                
                uintmax_t result = *static_cast<uintmax_t*>( LogicalOrExpr->data ) ;

                if( result )
                {
                    LControllingExpr->eval() ;
                    replaceDataVoid( LControllingExpr->data, data ) ;
                }
                else
                {
                    RControllingExpr->eval() ;
                    replaceDataVoid( RControllingExpr->data, data ) ;
                }        

		std::cout << "L type: " << LControllingExpr->evalType() << " r type: " << RControllingExpr->evalType() << " utype: " << FT_UNSIGNED_LONG_INT << std::endl ;
		//if( FT_UNSIGNED_LONG_INT == LControllingExpr->type || FT_UNSIGNED_LONG_INT == RControllingExpr->type )
		if( isUnsignedType( LControllingExpr->evalType() ) || isUnsignedType( RControllingExpr->evalType() ) )
		{
			std::cout << "Promote to unsigned" << std::endl ;
			type = FT_UNSIGNED_LONG_INT ;
		}
            }
            else if( LogicalOrExpr )
            {
		    std::cout << "controllingExprAST -> eval -> LogicalOR" << std::endl ;
                LogicalOrExpr->eval() ;
                copyData( LogicalOrExpr ) ;
		std::cout << "controllingExprAST -> eval -> LogicalOR done" << std::endl ;
            }
        }

	virtual EFundamentalType evalType()
	{
		std::cout << "ContrllingExpr evalType -> " << std::endl ;
		if( LControllingExpr && RControllingExpr )
		{
			if( isUnsignedType( LControllingExpr->evalType() ) || 
					isUnsignedType( RControllingExpr->evalType() ) )
			{
				return FT_UNSIGNED_LONG_INT ;
			}
		}
		else
		{
			return LogicalOrExpr->evalType() ;
		}

		return type ;
	} 
        
        bool dataAsBool() { return voidPtrToBool( data ) ; } ;
        
        void setLogicalOr( logicalOrExprAST *lor )
        {
            LogicalOrExpr = lor ;
        }
        
        void setLeftCtrlExpr( controllingExprAST *cet )
        {
            LControllingExpr = cet ;
        }
        
        void setRightCtrlExpr( controllingExprAST *cet )
        {
            RControllingExpr = cet ;
        }

    private:
        logicalOrExprAST
            *LogicalOrExpr ;
        controllingExprAST
            *LControllingExpr,
            *RControllingExpr ;
} ;


class primaryExprAST : public ExprAST
{
    public:
        primaryExprAST() : cExp(nullptr)  {} 
        virtual ~primaryExprAST() {} 
        
        virtual void eval() 
        {
		std::cout << "primaryExprAST -> eval" ;
            if( isDefined )
            {
			std::cout << " -> defined" << std::endl ;
                replaceData( PA3Mock_IsDefinedIdentifier(keywordOrIdentifer), data ) ;
                //type = FT_UNSIGNED_LONG_INT ;
                type = FT_LONG_INT ;
            }
            else if( isLiteral )
            {
		    if( FT_LONG_INT == type )
		    {
    			std::cout << " -> literal id: " << myId << " value: " << *static_cast<intmax_t*>(data) << std::endl ;
			type = FT_LONG_INT ;
		    }
		    else
		    {
    			std::cout << " -> literal id: " << myId << " value: " << *static_cast<uintmax_t*>(data) << std::endl ;
			type = FT_UNSIGNED_LONG_INT ;
		    }
            }
            else if( isIdOrKeyword )
            {
			std::cout << " -> id or keyword" << std::endl ;
                replaceData( 0, data ) ;
                type = FT_UNSIGNED_LONG_INT ;
                //type = FT_LONG_INT ;
            }
	        else if( cExp )
	        {
			std::cout << " -> controlling exp id: " << myId << std::endl ;
		      cExp->eval() ;
              
              	//replaceDataVoid( cExp->data, data ) ;
		      copyData( cExp ) ;
	        }
        }
        
        void setControllingExp( controllingExprAST* ce )
        {
            cExp = ce ;
        }

        controllingExprAST
            *cExp ;
        std::string
            keywordOrIdentifer ;
        bool
            isDefined,
            isIdOrKeyword,
            isLiteral ;
	int myId ;
	static int
		id ;
} ;

int primaryExprAST::id = 0 ;

primaryExprAST* parsePrimaryExpression( std::vector<PostTokenData> &ptd , size_t &currPos, size_t &endPos ) ;

unaryExprAST* parseUnaryExpression( std::vector<PostTokenData> &ptd , size_t &currPos, size_t &endPos )
{
    std::cout << "Parse Unary" << std::endl ;
    unaryExprAST *uet = new unaryExprAST() ;
    
    if( isValidPeek( ptd, currPos+1, endPos ) && 
        ( isOp( ptd, currPos, OP_PLUS ) || isOp( ptd, currPos, OP_MINUS ) || isOp( ptd, currPos, OP_LNOT ) || isOp( ptd, currPos, OP_COMPL ) ) ) 
    {
        uet->op = getOp( ptd, currPos ) ;
        
        if( !isValidPeek( ptd, currPos+1, endPos) )
        {
            throw std::logic_error("Ill-formed unary expression ... expecting expression after \" +/-/!/~ \"") ;
        }
        
        currPos += 1 ; // Eat op and advance to next token
        uet->setUnary( parseUnaryExpression( ptd, currPos, endPos ) ) ; // Process and eat
    }
    else
    {
        uet->setPrimary( parsePrimaryExpression( ptd, currPos, endPos ) ) ; // Process and eat
    }
    
    return uet ;
}

multiplicativeExprAST* parseMultiplicativeExpression( std::vector<PostTokenData> &ptd , size_t &currPos, size_t &endPos, ExprAST *left  )
{
    std::cout << "Parse Mul" << std::endl ;
    multiplicativeExprAST *mulet = new multiplicativeExprAST() ;
    
    if( isValidPeek( ptd, currPos+1, endPos ) && 
        ( isOp( ptd, currPos+1, OP_STAR ) || isOp( ptd, currPos+1, OP_DIV ) || isOp( ptd, currPos+1, OP_MOD ) ) ) 
    {
        mulet->op = getOp( ptd, currPos+1 ) ;
        
        if( nullptr != left )
        {
            mulet->setMul( left ) ;
            ++currPos ;
        }
        else
        {
            mulet->setMul( parseMultiplicativeExpression( ptd, currPos, currPos, nullptr ) ) ; // Process and eat
        }
        
        if( !isValidPeek( ptd, currPos+1, endPos) )
        {
            throw std::logic_error("Ill-formed mul expression ... expecting expression after \" */\\/% \"") ;
        }
        
        currPos += 1 ; // Eat || and advance to next token
        
        mulet->setUnary( parseUnaryExpression( ptd, currPos, endPos ) ) ; // Process and eat
    }
    else
    {
        mulet->setUnary( parseUnaryExpression( ptd, currPos, endPos ) ) ; // Process and eat
    }
    
    return mulet ;
}

additiveExprAST* parseAdditiveExpression( std::vector<PostTokenData> &ptd , size_t &currPos, size_t &endPos, ExprAST *left )
{
    std::cout << "Parse Add" << std::endl ;
    additiveExprAST *addet = new additiveExprAST() ;
    
    if( isValidPeek( ptd, currPos+1, endPos) && 
        ( isOp( ptd, currPos+1, OP_PLUS ) || isOp( ptd, currPos+1, OP_MINUS )  ) ) 
    {
        addet->op = getOp( ptd, currPos+1 ) ;
        if( nullptr != left )
        {
            addet->setAdditive( left ) ;
            ++currPos ;
        }
        else
        {
        	addet->setAdditive( parseAdditiveExpression( ptd, currPos, currPos, nullptr ) ) ; // Process and eat
	    }

        if( !isValidPeek( ptd, currPos+1, endPos) )
        {
            throw std::logic_error("Ill-formed additive expression ... expecting expression after \" +/- \"") ;
        }
        
        currPos += 1 ; // Eat || and advance to next token
        addet->setMul( parseMultiplicativeExpression( ptd, currPos, endPos, nullptr ) ) ; // Process and eat
    }
    else
    {
    	std::cout << "Parse Add Mul" << std::endl ;
        addet->setMul( parseMultiplicativeExpression( ptd, currPos, endPos, nullptr ) ) ; // Process and eat
    }
    return addet ;
}

shiftExprAST* parseShiftExpression( std::vector<PostTokenData> &ptd , size_t &currPos, size_t &endPos, ExprAST *left )
{
    std::cout << "Parse shift" << std::endl ;
    shiftExprAST *shet = new shiftExprAST() ;
    
    if( isValidPeek( ptd, currPos+1, endPos ) && 
        ( isOp( ptd, currPos+1, OP_LSHIFT ) || isOp( ptd, currPos+1, OP_RSHIFT )  ) ) 
    {   
        shet->op = getOp( ptd, currPos+1 ) ;
        
        if( nullptr != left )
        {
            shet->setShift( left ) ;
            ++currPos ;
        }
        else
        {
            shet->setShift( parseShiftExpression( ptd, currPos, currPos, nullptr ) ) ; // Process and eat
        }

        if( !isValidPeek( ptd, currPos+1, endPos ) )
        {
            throw std::logic_error("Ill-formed shift expression ... expecting expression after \" >> / << \"") ;
        }
        
        currPos += 1 ; // Eat || and advance to next token   
        shet->setAdditive( parseAdditiveExpression( ptd, currPos, endPos, nullptr ) ) ; // Process and eat
    }
    else
    {
        shet->setAdditive( parseAdditiveExpression( ptd, currPos, endPos, nullptr ) ) ; // Process and eat
    }
    
    return shet ;
}


relationalExprAST* parseRelationalExpression( std::vector<PostTokenData> &ptd , size_t &currPos, size_t &endPos, ExprAST *left )
{
    std::cout << "Parse rel" << std::endl ;
    relationalExprAST *ret = new relationalExprAST() ;
    
    if( isValidPeek( ptd, currPos+1, endPos ) && 
        ( isOp( ptd, currPos+1, OP_LT ) || isOp( ptd, currPos+1, OP_GT ) || isOp( ptd, currPos+1, OP_LE ) || isOp( ptd, currPos+1, OP_GE ) ) ) 
    {
        ret->op = getOp( ptd, currPos+1 ) ;
        
        if( nullptr != left )
        {
            ret->setRelational( left ) ;
            ++currPos ;
        }
        else
        {
            ret->setRelational( parseRelationalExpression( ptd, currPos, currPos, nullptr ) ) ; // Process and eat
        }

        if( !isValidPeek( ptd, currPos+1, endPos ) )
        {
            throw std::logic_error("Ill-formed relational expression ... expecting expression after \"> / >= / < / <= \"") ;
        }
        
        currPos += 1 ; // Eat || and advance to next token
        
        ret->setShift( parseShiftExpression( ptd, currPos, endPos, nullptr ) ) ; // Process and eat
    }
    else
    {
        ret->setShift( parseShiftExpression( ptd, currPos, endPos, nullptr ) ) ; // Process and eat
    }
    
    return ret ;
}

equalityExprAST* parseEqualityExpression( std::vector<PostTokenData> &ptd , size_t &currPos, size_t &endPos )
{
    std::cout << "Parse Equl" << std::endl ;
    equalityExprAST *eqet = new equalityExprAST() ;
    
    if( isValidPeek( ptd, currPos+1, endPos ) && 
        ( isOp( ptd, currPos+1, OP_NE ) || isOp( ptd, currPos+1, OP_EQ ) ) ) 
    {
        eqet->op = getOp( ptd, currPos+1 ) ;
        
        eqet->setEquality( parseEqualityExpression( ptd, currPos, currPos ) ) ; // Process and eat

        if( !isValidPeek( ptd, currPos+1, endPos ) )
        {
            throw std::logic_error("Ill-formed equality expression ... expecting expression after \"==/!=\"") ;
        }
        
        currPos += 1 ; // Eat || and advance to next token
         
        eqet->setRelational( parseRelationalExpression( ptd, currPos, endPos, nullptr ) ) ; // Process and eat
    }
    else
    {
        eqet->setRelational( parseRelationalExpression( ptd, currPos, endPos, nullptr ) ) ; // Process and eat
    }
    
    return eqet ;
}

andExprAST* parseAndExpression( std::vector<PostTokenData> &ptd , size_t &currPos, size_t &endPos )
{
    std::cout << "Parse and" << std::endl ;
    andExprAST *andet = new andExprAST() ;
    
    if( isValidPeek( ptd, currPos+1, endPos ) && isOp( ptd, currPos+1, OP_AMP ) ) 
    {
        andet->setAnd( parseAndExpression( ptd, currPos, currPos ) ) ; // Process and eat

        if( !isValidPeek( ptd, currPos+1, endPos ) )
        {
            throw std::logic_error("Ill-formed and expression ... expecting expression after \"&&\"") ;
        }
        
        currPos += 1 ; // Eat || and advance to next token
        
        andet->setEquality( parseEqualityExpression( ptd, currPos, endPos ) ) ; // Process and eat
    }
    else
    {
        andet->setEquality( parseEqualityExpression( ptd, currPos, endPos ) ) ; // Process and eat
    }
    
    return andet ;
}

exclusiveOrExprAST* parseExclusiveOrExpression( std::vector<PostTokenData> &ptd , size_t &currPos, size_t &endPos )
{
    std::cout << "Parse xor" << std::endl ;
    exclusiveOrExprAST *eoret = new exclusiveOrExprAST() ;
    
    if( isValidPeek( ptd, currPos+1, endPos ) && isOp( ptd, currPos+1, OP_XOR ) ) 
    {
        eoret->setExclusiveOr( parseExclusiveOrExpression( ptd, currPos, currPos ) ) ; // Process and eat

        if( !isValidPeek( ptd, currPos+1, endPos ) )
        {
            throw std::logic_error("Ill-formed exclusive or expression ... expecting expression after \"^\"") ;
        }
        
        currPos += 1 ; // Eat || and advance to next token
        
        eoret->setAnd( parseAndExpression( ptd, currPos, endPos ) ) ; // Process and eat
    }
    else
    {
        eoret->setAnd( parseAndExpression( ptd, currPos, endPos ) ) ; // Process and eat
    }
    
    return eoret ;
}

inclusiveOrExprAST* parseInclusiveOrExpression( std::vector<PostTokenData> &ptd , size_t &currPos, size_t &endPos )
{
    std::cout << "Parse in or" << std::endl ;
    inclusiveOrExprAST *ioret = new inclusiveOrExprAST() ;
    
    if( isValidPeek( ptd, currPos+1, endPos ) && isOp( ptd, currPos+1, OP_BOR ) ) 
    {
        ioret->setInclusiveOr( parseInclusiveOrExpression( ptd, currPos, currPos ) ) ; // Process and eat
        
        if( !isValidPeek( ptd, currPos+1, endPos ) )
        {
            throw std::logic_error("Ill-formed inclusive or expression ... expecting expression after \"|\"") ;
        }
        
        currPos += 1 ; // Eat || and advance to next token
        
        ioret->setExclusiveOr( parseExclusiveOrExpression( ptd, currPos, endPos ) ) ; // Process and eat
    }
    else
    {
        ioret->setExclusiveOr( parseExclusiveOrExpression( ptd, currPos, endPos ) ) ; // Process and eat
    }
    
    return ioret ;
}


logicalAndExprAST* parseLogicalAndExpression( std::vector<PostTokenData> &ptd , size_t &currPos, size_t &endPos, ExprAST *left )
{
    std::cout << "Parse log and" << std::endl ;
    logicalAndExprAST *landet = new logicalAndExprAST() ;
    
    if( isValidPeek( ptd, currPos+1, endPos ) && isOp( ptd, currPos+1, OP_LAND ) ) // logical-or-expression OP_LAND logical-and-expression
    {
        if( nullptr != left )
        {
            landet->setLogicalAnd( left ) ;
            ++currPos ;
        }
        else
        {
            landet->setLogicalAnd( parseLogicalAndExpression( ptd, currPos, currPos, nullptr ) ) ; // Process and eat
        }
        
        if( !isValidPeek( ptd, currPos+1, endPos ) )
        {
            throw std::logic_error("Ill-formed logical and expression ... expecting expression after \"&&\"") ;
        }
        
        currPos += 1 ; // Eat || and advance to next token
        
        landet->setInclusiveOr( parseInclusiveOrExpression( ptd, currPos, endPos ) ) ; // Process and eat 
    }
    else
    {
        landet->setInclusiveOr( parseInclusiveOrExpression( ptd, currPos, endPos ) ) ; // Process and eat
    }
    
    return landet ;
}

logicalOrExprAST* parseLogicalOrExpression( std::vector<PostTokenData> &ptd , size_t &currPos, size_t &endPos, ExprAST *left )
{
    std::cout << "Parse log or" << std::endl ;
    logicalOrExprAST *loret = new logicalOrExprAST() ;
    
    if( isValidPeek( ptd, currPos+1, endPos ) && isOp( ptd, currPos+1, OP_LOR  ) ) // logical-or-expression OP_LOR logical-and-expression
    {
        if( nullptr != left)
        {
            loret->setLogicalOr( left ) ;
            ++currPos ;
        }
        else
        {
            loret->setLogicalOr( parseLogicalOrExpression( ptd, currPos, currPos, nullptr ) ) ; // Process and eat
        }
        
        if( !isValidPeek( ptd, currPos+1, endPos ) )
        {
            throw std::logic_error("Ill-formed logical Or expression ... expecting expression after \"||\"") ;
        }
        
        currPos += 1 ; // Eat || and advance to next token
        
        loret->setLogicalAnd( parseLogicalAndExpression( ptd, currPos, endPos, nullptr ) ) ; // Process and eat
    }
    else
    {
        loret->setLogicalAnd( parseLogicalAndExpression( ptd, currPos, endPos, nullptr ) ) ; // Process and eat
    }
    
    return loret ;
}

controllingExprAST* parseControllingExpression( std::vector<PostTokenData> &ptd , size_t &currPos, size_t &endPos )
{
    std::cout << "Parse controlling" << std::endl ;
    controllingExprAST *cet = new controllingExprAST() ;
    
    cet->type = ptd[currPos].type ;
    if( isOp( ptd, currPos, OP_RPAREN ) )
    {
            throw std::logic_error("Ill-formed controlling expression ... expecting expression found \")\"") ;
    }
    else if( isValidPeek( ptd, currPos+1, endPos ) && isOp( ptd, currPos+1, OP_QMARK ) )
    {
        cet->setLogicalOr( parseLogicalOrExpression( ptd, currPos, currPos, nullptr ) ) ; // Process and eat
        
        if( !isValidPeek( ptd, currPos+1, endPos ) )
        {
            throw std::logic_error("Ill-formed controlling expression ... expecting expression after \"?\"") ;
        }
        
        currPos += 1 ; // Eat ? and advance to next token
	size_t tmpPos = currPos ;

	while( isValidPeek( ptd, tmpPos, endPos ) && !isOp( ptd, tmpPos, OP_COLON ) )
	{
		++tmpPos ;
	}

        cet->setLeftCtrlExpr( parseControllingExpression( ptd, currPos, tmpPos ) ) ; // Process and eat
        
        if( !isOp( ptd, currPos, OP_COLON ) ) 
        {
            throw std::logic_error("Ill-formed controlling expression ... expecting \":\"") ;
        }
        else if( !isValidPeek( ptd, currPos+1, endPos ) )
        {
            throw std::logic_error("Ill-formed controlling expression ... expecting expression after \":\"") ;
        }
        
        currPos += 1 ; // Eat : and advance to next token
        cet->setRightCtrlExpr( parseControllingExpression( ptd, currPos, endPos ) ) ; // Process and eat
    }
    else
    {
        cet->setLogicalOr( parseLogicalOrExpression( ptd, currPos, endPos, nullptr ) ) ; // Process and eat
    }
    
    return cet ;
}

primaryExprAST* parsePrimaryExpression( std::vector<PostTokenData> &ptd , size_t &currPos, size_t &endPos )
{
    std::cout << "Parse primary pos: " << currPos << std::endl ;
    primaryExprAST *pet = new primaryExprAST() ;
    
    if( hasType( ptd, currPos ) )
    {
        if( isArray( ptd, currPos ) )
        {
            throw std::logic_error("Arrays not allow when processing integral expressions");
        }
        else if( isIntegralType( ptd, currPos ) )
        {
            throw std::logic_error("not integral type");
        }
        
        pet->isLiteral = true ;
        pet->isDefined = pet->isIdOrKeyword = false ;
        //replaceData( *static_cast<uintmax_t*>(ptd[currPos].data), pet->data ) ;
	replaceDataVoid( ptd[currPos].data, pet->data ) ;
        
        std::cout << "count: " << integralSignedTypesSet.count( ptd[currPos].type ) << std::endl ;
        
        if( integralSignedTypesSet.count( ptd[currPos].type ) != 0 )
        {
            std::cout << "Signed type" << std::endl ;
            pet->type = FT_LONG_INT ;
        }
        else
        {
            pet->type = FT_UNSIGNED_LONG_INT ;
        }

	if( FT_LONG_INT == pet->type && 0 == *static_cast<intmax_t*>(pet->data) )
	{
		std::cout << " ZERO!!" << std::endl ;
	}
	else if( 0 == *static_cast<uintmax_t*>(pet->data) )
	{
		std::cout << " ZERO!!" << std::endl ;
	}
        
	pet->myId = pet->id ;
	++pet->id ;
	if( FT_LONG_INT == pet->type )
	{
       		std::cout << "Literal id: " << pet->myId << " value: " << *static_cast<intmax_t*>(pet->data) << " Type: " << ptd[currPos].type << std::endl ;
	}
	else
	{
        	std::cout << "Literal id: " << pet->myId << " value: " << *static_cast<uintmax_t*>(pet->data) << " Type: " << ptd[currPos].type << std::endl ;
	}
        
        ++currPos ;
    }
    else if( hasIdentifier( ptd, currPos ) )
    {
        if( "defined" == ptd[currPos].sourceOrId )
        {
            std::cout << "Defined" << std::endl ;
            if( isValidPeek( ptd, currPos+1, endPos ) )
            {
                ++currPos ;
                if( hasIdentifier( ptd, currPos ) ) // defined identifier_or_keyword
                {
                    std::cout << "defined ID" << std::endl ;
                    pet->keywordOrIdentifer = ptd[currPos].sourceOrId ;
                    ++currPos ;
                }
                else if( isOp( ptd, currPos,OP_LPAREN) ) // defined OP_LPAREN identifier_or_keyword OP_RPAREN
                {
                    std::cout << "defined( ID )" << std::endl ;
                    if( isValidPeek( ptd, currPos+2, endPos ) )
                    {
                        if( isOp( ptd, currPos+2, OP_RPAREN ) &&
                             hasIdentifier( ptd, currPos+1 ) )
                        {
                            pet->keywordOrIdentifer = ptd[currPos+1].sourceOrId ;
                        }
                        else
                        {
                            throw std::logic_error("Ill-formed defined, expected \"identifier )\" but have different types") ;
                        }
                             
                    }
                    else
                    {
                        throw std::logic_error("Ill-formed defined, not enough data, expected \"identifier )\"") ;
                    }
                    currPos += 2 ;
                }
            }
            else
            {
                throw std::logic_error("Ill-formed defined, expected identifier or (") ;
            }
            pet->isDefined = true ;
            pet->isLiteral = pet->isIdOrKeyword = false ;
        }
    }
    else if( isOp( ptd, currPos, OP_LPAREN ) ) // OP_LPAREN controlling-expression OP_RPAREN
    {
	std::cout << "Open paren (" << std::endl ;
        ++currPos ;
        pet->isDefined = pet->isLiteral = pet->isIdOrKeyword = false ;
        pet->setControllingExp( parseControllingExpression( ptd, currPos, endPos ) );
	if( !isOp( ptd, currPos, OP_RPAREN ) )
	{
		throw std::logic_error("Ill-formed defined, expected )") ;
	}
	++currPos ;
	std::cout << "Close paren )" << std::endl ;
    }
    
    return pet ;
}
 
void parse( std::vector<PostTokenData> &ptd )
{
    size_t
	    pos =  0,
        peekPos = 0,
	    endPos = ptd.size();

    if( pos == endPos )
    {
	    return ;
    }

    ExprAST *p = nullptr ;

    try
    {
    do
    {
        std::cout << "pos: " << pos << " endPos: " << endPos << std::endl ;
        
        
    if( isValidPeek( ptd, pos+1, endPos) && 
        ( isOp( ptd, pos+1, OP_PLUS ) || isOp( ptd, pos+1, OP_MINUS )  ) ) 
    {
    	p = parseAdditiveExpression( ptd, pos, endPos, p ) ;
    }
    else if( isValidPeek( ptd, pos+1, endPos ) && 
        ( isOp( ptd, pos, OP_PLUS ) || isOp( ptd, pos, OP_MINUS ) || isOp( ptd, pos, OP_LNOT ) || isOp( ptd, pos, OP_COMPL ) ) ) 
    {
    	p = parseUnaryExpression( ptd, pos, endPos ) ;
    }
    else if( isValidPeek( ptd, pos+1, endPos ) && isOp( ptd, pos+1, OP_QMARK ) )
    {
	    std::cout << "Controlling parse" << std::endl ;
    	p = parseControllingExpression( ptd, pos, endPos ) ;
    }
    else if( isValidPeek( ptd, pos+1, endPos ) && isOp( ptd, pos+1, OP_LOR  ) ) // logical-or-expression OP_LOR logical-and-expression
    {
    	p = parseLogicalOrExpression( ptd, pos, endPos, p ) ;
    }
    else if( isValidPeek( ptd, pos+1, endPos ) && isOp( ptd, pos+1, OP_LAND ) ) // logical-or-expression OP_LAND logical-and-expression
    {
    	p = parseLogicalAndExpression( ptd, pos, endPos, p ) ;
    }
    else if( isValidPeek( ptd, pos+1, endPos ) && isOp( ptd, pos+1, OP_BOR ) ) 
    {
    	p = parseInclusiveOrExpression( ptd, pos, endPos ) ;
    }
    else if( isValidPeek( ptd, pos+1, endPos ) && isOp( ptd, pos+1, OP_XOR ) ) 
    {
    	p = parseExclusiveOrExpression( ptd, pos, endPos ) ;
    }
    else if( isValidPeek( ptd, pos+1, endPos ) && isOp( ptd, pos+1, OP_AMP ) ) 
    {
    	p = parseAndExpression( ptd, pos, endPos ) ;
    }
    else if( isValidPeek( ptd, pos+1, endPos ) && 
        ( isOp( ptd, pos+1, OP_NE ) || isOp( ptd, pos+1, OP_EQ ) ) ) 
    {
    	p = parseEqualityExpression( ptd, pos, endPos ) ;
    }
    else if( isValidPeek( ptd, pos+1, endPos ) && 
        ( isOp( ptd, pos+1, OP_LT ) || isOp( ptd, pos+1, OP_GT ) || isOp( ptd, pos+1, OP_LE ) || isOp( ptd, pos+1, OP_GE ) ) ) 
    {
    	p = parseRelationalExpression( ptd, pos, endPos, p ) ;
    }
    else if( isValidPeek( ptd, pos+1, endPos ) && 
        ( isOp( ptd, pos+1, OP_LSHIFT ) || isOp( ptd, pos+1, OP_RSHIFT )  ) ) 
    {
    	p = parseShiftExpression( ptd, pos, endPos, p ) ;
    }
    else if( isValidPeek( ptd, pos+1, endPos ) && 
        ( isOp( ptd, pos+1, OP_STAR ) || isOp( ptd, pos+1, OP_DIV ) || isOp( ptd, pos+1, OP_MOD ) ) ) 
    {
    	p = parseMultiplicativeExpression( ptd, pos, endPos, p ) ;
    }
    else
    {
    	p = parsePrimaryExpression( ptd, pos, endPos ) ;
    }
    
        if( pos >= endPos -1 )
        {
            break ;
        }
        --pos ;
    } while( pos < endPos-1 ) ;

    std::cout << "pos: " << pos << " endPos: " << endPos << std::endl ;

    p->eval() ;
    std::cout << "p->type: " << p->type << std::endl ;

    //if( p->type == FT_UNSIGNED_LONG_INT )
    if( p->evalType() == FT_UNSIGNED_LONG_INT )
    {
        std::cout << *static_cast<uintmax_t*>(p->data) << "u" << std::endl ;
    }
    else
    {
        std::cout << *static_cast<intmax_t*>(p->data) << std::endl ;
    }

    std::cout << std::endl << std::endl ;
    }
    catch( std::exception& e)
    {
	    std::cout << "error" << std::endl << std::endl << std::endl ;
	    std::cout << e.what() << std::endl ;
    }
}
 
int main()
{
    unsigned int x = 100 ;
    void * vptr = &x ;
    
    bool b1 = voidPtrToBool( vptr ) ;
    std::cout << "bool check: " << b1 << std::endl ;
    
    x = 0 ;
    b1 = voidPtrToBool( vptr ) ;
    std::cout << "bool check: " << b1 << std::endl ;
    
    std::vector<PostTokenData> ptd ;
    
    int i1 ;
    std::string str1 ;
    
    str1 = "true" ;
    ptd.push_back( PostTokenData( str1, "", "", EPT_SIMPLE, FT_CHAR, static_cast<const void*>( str1.c_str()), str1.size() , true ) );
    
    str1 = "?" ;
    ptd.push_back( PostTokenData( str1, "", "", EPT_SIMPLE, FT_CHAR, static_cast<const void*>( str1.c_str()), str1.size() , true ) );
    
    i1 = 9u ;
    ptd.push_back( PostTokenData( "9u", "", "", EPT_TYPE, FT_UNSIGNED_INT, &i1, sizeof(int), false ) ) ;
    
    str1 = ":" ;
    ptd.push_back( PostTokenData( str1, "", "", EPT_SIMPLE, FT_CHAR, static_cast<const void*>( str1.c_str()), str1.size() , true ) );
    
    i1 = 5 ;
    ptd.push_back( PostTokenData( "5", "", "", EPT_TYPE, FT_INT, &i1, sizeof(int), false ) ) ;

    str1 = "*" ;
    ptd.push_back( PostTokenData( str1, "", "", EPT_SIMPLE, FT_CHAR, static_cast<const void*>( str1.c_str()), str1.size() , true ) );
    
    i1 = 64 ;
    ptd.push_back( PostTokenData( "64", "", "", EPT_TYPE, FT_INT, &i1, sizeof(int), false ) ) ;
    
    parse( ptd ) ; ptd.clear() ;
    
    // 0&&(5<<-1)
    i1 = 1 ;
    ptd.push_back( PostTokenData( "1", "", "", EPT_TYPE, FT_INT, &i1, sizeof(int), false ) ) ;
    
    str1 = "||" ;
    ptd.push_back( PostTokenData( str1, "", "", EPT_SIMPLE, FT_CHAR, static_cast<const void*>( str1.c_str()), str1.size() , true ) );

    str1 = "(" ;
    ptd.push_back( PostTokenData( str1, "", "", EPT_SIMPLE, FT_CHAR, static_cast<const void*>( str1.c_str()), str1.size() , true ) );

    i1 = 5 ;
    ptd.push_back( PostTokenData( "5", "", "", EPT_TYPE, FT_INT, &i1, sizeof(int), false ) ) ;
    
    str1 = "<<" ;
    ptd.push_back( PostTokenData( str1, "", "", EPT_SIMPLE, FT_CHAR, static_cast<const void*>( str1.c_str()), str1.size() , true ) );
    
    str1 = "-" ;
    ptd.push_back( PostTokenData( str1, "", "", EPT_SIMPLE, FT_CHAR, static_cast<const void*>( str1.c_str()), str1.size() , true ) );
    
    i1 = 1 ;
    ptd.push_back( PostTokenData( "1", "", "", EPT_TYPE, FT_INT, &i1, sizeof(int), false ) ) ;

    str1 = ")" ;
    ptd.push_back( PostTokenData( str1, "", "", EPT_SIMPLE, FT_CHAR, static_cast<const void*>( str1.c_str()), str1.size() , true ) );


    parse( ptd ) ; ptd.clear() ;
    
	//
	// 1 ? 10 : 20
	//
    i1 = 1 ;
    ptd.push_back( PostTokenData( "1", "", "", EPT_TYPE, FT_INT, &i1, sizeof(int), false ) ) ;
    
    str1 = "?" ;
    ptd.push_back( PostTokenData( str1, "", "", EPT_SIMPLE, FT_CHAR, static_cast<const void*>( str1.c_str()), str1.size() , true ) );
    
    i1 = 10 ;
    ptd.push_back( PostTokenData( "10", "", "", EPT_TYPE, FT_INT, &i1, sizeof(int), false ) ) ;
    
    str1 = ":" ;
    ptd.push_back( PostTokenData( str1, "", "", EPT_SIMPLE, FT_CHAR, static_cast<const void*>( str1.c_str()), str1.size() , true ) );
    
    i1 = 20 ;
    ptd.push_back( PostTokenData( "20", "", "", EPT_TYPE, FT_INT, &i1, sizeof(int), false ) ) ;
    
    parse( ptd ) ; ptd.clear() ;

	//
	// 0 || 20 
	//
    i1 = 0 ;
    ptd.push_back( PostTokenData( "0", "", "", EPT_TYPE, FT_INT, &i1, sizeof(int), false ) ) ;
    
    str1 = "||" ;
    ptd.push_back( PostTokenData( str1, "", "", EPT_SIMPLE, FT_CHAR, static_cast<const void*>( str1.c_str()), str1.size() , true ) );
    
    i1 = 20 ;
    ptd.push_back( PostTokenData( "20", "", "", EPT_TYPE, FT_INT, &i1, sizeof(int), false ) ) ;
    
    parse( ptd ) ; ptd.clear() ;

	//
	// false || true 
	//
    str1 = "false";
    ptd.push_back( PostTokenData( str1, "", "", EPT_SIMPLE, FT_CHAR, static_cast<const void*>( str1.c_str()), str1.size() , true ) );

    str1 = "||" ;
    ptd.push_back( PostTokenData( str1, "", "", EPT_SIMPLE, FT_CHAR, static_cast<const void*>( str1.c_str()), str1.size() , true ) );

    str1 = "true";
    ptd.push_back( PostTokenData( str1, "", "", EPT_SIMPLE, FT_CHAR, static_cast<const void*>( str1.c_str()), str1.size() , true ) );

    parse( ptd ) ; ptd.clear() ;
    

	//
	//  1 | 2 
	//
    i1 = 1 ;
    ptd.push_back( PostTokenData( "1", "", "", EPT_TYPE, FT_INT, &i1, sizeof(int), false ) ) ;
    
    str1 = "|" ;
    ptd.push_back( PostTokenData( str1, "", "", EPT_SIMPLE, FT_CHAR, static_cast<const void*>( str1.c_str()), str1.size() , true ) );
    
    i1 = 2 ;
    ptd.push_back( PostTokenData( "2", "", "", EPT_TYPE, FT_INT, &i1, sizeof(int), false ) ) ;
    
    parse( ptd ) ; ptd.clear() ;

	//
	//  10 ^ 15 
	//
    i1 = 10 ;
    ptd.push_back( PostTokenData( "10", "", "", EPT_TYPE, FT_INT, &i1, sizeof(int), false ) ) ;
    
    str1 = "^" ;
    ptd.push_back( PostTokenData( str1, "", "", EPT_SIMPLE, FT_CHAR, static_cast<const void*>( str1.c_str()), str1.size() , true ) );
    
    i1 = 15 ;
    ptd.push_back( PostTokenData( "15", "", "", EPT_TYPE, FT_INT, &i1, sizeof(int), false ) ) ;
    
    parse( ptd ) ; ptd.clear() ;

	//
	//  14 & 3 
	//
    i1 = 14 ;
    ptd.push_back( PostTokenData( "14", "", "", EPT_TYPE, FT_INT, &i1, sizeof(int), false ) ) ;
    
    str1 = "&" ;
    ptd.push_back( PostTokenData( str1, "", "", EPT_SIMPLE, FT_CHAR, static_cast<const void*>( str1.c_str()), str1.size() , true ) );
    
    i1 = 3 ;
    ptd.push_back( PostTokenData( "3", "", "", EPT_TYPE, FT_INT, &i1, sizeof(int), false ) ) ;
    
    parse( ptd ) ; ptd.clear() ;

	//
	//  14 == 14
	//
    i1 = 14 ;
    ptd.push_back( PostTokenData( "14", "", "", EPT_TYPE, FT_INT, &i1, sizeof(int), false ) ) ;
    
    str1 = "==" ;
    ptd.push_back( PostTokenData( str1, "", "", EPT_SIMPLE, FT_CHAR, static_cast<const void*>( str1.c_str()), str1.size() , true ) );
    
    i1 = 14 ;
    ptd.push_back( PostTokenData( "14", "", "", EPT_TYPE, FT_INT, &i1, sizeof(int), false ) ) ;
    
    parse( ptd ) ; ptd.clear() ;

	//
	//  14 != 14
	//
    i1 = 14 ;
    ptd.push_back( PostTokenData( "14", "", "", EPT_TYPE, FT_INT, &i1, sizeof(int), false ) ) ;
    
    str1 = "!=" ;
    ptd.push_back( PostTokenData( str1, "", "", EPT_SIMPLE, FT_CHAR, static_cast<const void*>( str1.c_str()), str1.size() , true ) );
    
    i1 = 14 ;
    ptd.push_back( PostTokenData( "14", "", "", EPT_TYPE, FT_INT, &i1, sizeof(int), false ) ) ;
    
    parse( ptd ) ; ptd.clear() ;


	//
	//  14 < 5 
	//
  i1 = 14 ;
    ptd.push_back( PostTokenData( "14", "", "", EPT_TYPE, FT_INT, &i1, sizeof(int), false ) ) ;
    
    str1 = "<" ;
    ptd.push_back( PostTokenData( str1, "", "", EPT_SIMPLE, FT_CHAR, static_cast<const void*>( str1.c_str()), str1.size() , true ) );
    
    i1 = 5 ;
    ptd.push_back( PostTokenData( "5", "", "", EPT_TYPE, FT_INT, &i1, sizeof(int), false ) ) ;
    
    parse( ptd ) ; ptd.clear() ;

    //
	//  1 << 3 
	//
    i1 = 1 ;
    ptd.push_back( PostTokenData( "1", "", "", EPT_TYPE, FT_INT, &i1, sizeof(int), false ) ) ;
    
    str1 = "<<" ;
    ptd.push_back( PostTokenData( str1, "", "", EPT_SIMPLE, FT_CHAR, static_cast<const void*>( str1.c_str()), str1.size() , true ) );
    
    i1 = 3 ;
    ptd.push_back( PostTokenData( "3", "", "", EPT_TYPE, FT_INT, &i1, sizeof(int), false ) ) ;
    
    parse( ptd ) ; ptd.clear() ;
    

	//
	// 2 * 5
	//
    i1 = 2u ;
    ptd.push_back( PostTokenData( "2u", "", "", EPT_TYPE, FT_UNSIGNED_INT, &i1, sizeof(int), false ) ) ;
    
    str1 = "*" ;
    ptd.push_back( PostTokenData( str1, "", "", EPT_SIMPLE, FT_CHAR, static_cast<const void*>( str1.c_str()), str1.size() , true ) );
    
    i1 = 5 ;
    ptd.push_back( PostTokenData( "5", "", "", EPT_TYPE, FT_INT, &i1, sizeof(int), false ) ) ;
    
    parse( ptd ) ; ptd.clear() ;

	
    long l1 ;
    l1 = 2000000000 ;
    ptd.push_back( PostTokenData( "2000000000", "", "", EPT_TYPE, FT_INT, &l1, sizeof(long), false ) ) ;
    
    str1 = "*" ;
    ptd.push_back( PostTokenData( str1, "", "", EPT_SIMPLE, FT_CHAR, static_cast<const void*>( str1.c_str()), str1.size() , true ) );
    
    l1 = 9000000000 ;
    ptd.push_back( PostTokenData( "900000000", "", "", EPT_TYPE, FT_INT, &l1, sizeof(long), false ) ) ;
    
    parse( ptd ) ; ptd.clear() ;
    
    
    i1 = 521 ;
    ptd.push_back( PostTokenData( "521", "", "", EPT_TYPE, FT_INT, &i1, sizeof(int), false ) ) ;
    
    str1 = "*" ;
    ptd.push_back( PostTokenData( str1, "", "", EPT_SIMPLE, FT_CHAR, static_cast<const void*>( str1.c_str()), str1.size() , true ) );
    
    i1 = 521 ;
    ptd.push_back( PostTokenData( "521", "", "", EPT_TYPE, FT_INT, &i1, sizeof(int), false ) ) ;

    str1 = "*" ;
    ptd.push_back( PostTokenData( str1, "", "", EPT_SIMPLE, FT_CHAR, static_cast<const void*>( str1.c_str()), str1.size() , true ) );
    
    i1 = 124u ;
    ptd.push_back( PostTokenData( "124u", "", "", EPT_TYPE, FT_UNSIGNED_INT, &i1, sizeof(int), false ) ) ;
    
    parse( ptd ) ; ptd.clear() ;
    
    i1 = 521 ;
    ptd.push_back( PostTokenData( "521", "", "", EPT_TYPE, FT_INT, &i1, sizeof(int), false ) ) ;
    
    str1 = "*" ;
    ptd.push_back( PostTokenData( str1, "", "", EPT_SIMPLE, FT_CHAR, static_cast<const void*>( str1.c_str()), str1.size() , true ) );
    
    i1 = 521 ;
    ptd.push_back( PostTokenData( "521", "", "", EPT_TYPE, FT_INT, &i1, sizeof(int), false ) ) ;
    
    str1 = "*" ;
    ptd.push_back( PostTokenData( str1, "", "", EPT_SIMPLE, FT_CHAR, static_cast<const void*>( str1.c_str()), str1.size() , true ) );
    
    str1 = "~" ;
    ptd.push_back( PostTokenData( str1, "", "", EPT_SIMPLE, FT_CHAR, static_cast<const void*>( str1.c_str()), str1.size() , true ) );
    
    char c1 ;
    c1 = 'z' ;
    ptd.push_back( PostTokenData( "'z'", "", "", EPT_TYPE, FT_CHAR, &c1, 1 , false ) );
    
    parse( ptd ) ; ptd.clear() ;

    i1 = 521 ;
    ptd.push_back( PostTokenData( "521", "", "", EPT_TYPE, FT_INT, &i1, sizeof(int), false ) ) ;
    
    str1 = "*" ;
    ptd.push_back( PostTokenData( str1, "", "", EPT_SIMPLE, FT_CHAR, static_cast<const void*>( str1.c_str()), str1.size() , true ) );
    
    i1 = 521 ;
    ptd.push_back( PostTokenData( "521", "", "", EPT_TYPE, FT_INT, &i1, sizeof(int), false ) ) ;

    str1 = "*" ;
    ptd.push_back( PostTokenData( str1, "", "", EPT_SIMPLE, FT_CHAR, static_cast<const void*>( str1.c_str()), str1.size() , true ) );

    str1 = "-" ;
    ptd.push_back( PostTokenData( str1, "", "", EPT_SIMPLE, FT_CHAR, static_cast<const void*>( str1.c_str()), str1.size() , true ) );
    
    i1 = 4;
    ptd.push_back( PostTokenData( "4", "", "", EPT_TYPE, FT_INT, &i1, sizeof(int), false ) ) ;
    
    parse( ptd ) ; ptd.clear() ;

	
    str1 = "true" ;
    ptd.push_back( PostTokenData( str1, "", "", EPT_SIMPLE, FT_CHAR, static_cast<const void*>( str1.c_str()), str1.size() , true ) );
    
    str1 = "?" ;
    ptd.push_back( PostTokenData( str1, "", "", EPT_SIMPLE, FT_CHAR, static_cast<const void*>( str1.c_str()), str1.size() , true ) );
    
    i1 = 5 ;
    ptd.push_back( PostTokenData( "5", "", "", EPT_TYPE, FT_INT, &i1, sizeof(int), false ) ) ;
    
    str1 = ":" ;
    ptd.push_back( PostTokenData( str1, "", "", EPT_SIMPLE, FT_CHAR, static_cast<const void*>( str1.c_str()), str1.size() , true ) );
    
    i1 = 5 ;
    ptd.push_back( PostTokenData( "5", "", "", EPT_TYPE, FT_INT, &i1, sizeof(int), false ) ) ;

    str1 = "<<" ;
    ptd.push_back( PostTokenData( str1, "", "", EPT_SIMPLE, FT_CHAR, static_cast<const void*>( str1.c_str()), str1.size() , true ) );
    
    i1 = 64 ;
    ptd.push_back( PostTokenData( "64", "", "", EPT_TYPE, FT_INT, &i1, sizeof(int), false ) ) ;
    
    parse( ptd ) ; ptd.clear() ;

    i1 = 2 ;
    ptd.push_back( PostTokenData( "2", "", "", EPT_TYPE, FT_INT, &i1, sizeof(int), false ) ) ;
    
    str1 = "*" ;
    ptd.push_back( PostTokenData( str1, "", "", EPT_SIMPLE, FT_CHAR, static_cast<const void*>( str1.c_str()), str1.size() , true ) );

    i1 = 2 ;
    ptd.push_back( PostTokenData( "2", "", "", EPT_TYPE, FT_INT, &i1, sizeof(int), false ) ) ;
    
    str1 = "<<" ;
    ptd.push_back( PostTokenData( str1, "", "", EPT_SIMPLE, FT_CHAR, static_cast<const void*>( str1.c_str()), str1.size() , true ) );
    
    i1 = 4 ;
    ptd.push_back( PostTokenData( "1", "", "", EPT_TYPE, FT_INT, &i1, sizeof(int), false ) ) ;
    
    parse( ptd ) ; ptd.clear() ;
    
    //
    //  14 > 5 
	//
    i1 = 10 ;
    ptd.push_back( PostTokenData( "10", "", "", EPT_TYPE, FT_INT, &i1, sizeof(int), false ) ) ;
    
    str1 = "+" ;
    ptd.push_back( PostTokenData( str1, "", "", EPT_SIMPLE, FT_CHAR, static_cast<const void*>( str1.c_str()), str1.size() , true ) );
    
    i1 = 14 ;
    ptd.push_back( PostTokenData( "14", "", "", EPT_TYPE, FT_INT, &i1, sizeof(int), false ) ) ;
    
    str1 = ">" ;
    ptd.push_back( PostTokenData( str1, "", "", EPT_SIMPLE, FT_CHAR, static_cast<const void*>( str1.c_str()), str1.size() , true ) );
    
    i1 = 100 ;
    ptd.push_back( PostTokenData( "100", "", "", EPT_TYPE, FT_INT, &i1, sizeof(int), false ) ) ;
    
    parse( ptd ) ; ptd.clear() ;
    
    str1 = "false";
    ptd.push_back( PostTokenData( str1, "", "", EPT_SIMPLE, FT_CHAR, static_cast<const void*>( str1.c_str()), str1.size() , true ) );

    str1 = "||" ;
    ptd.push_back( PostTokenData( str1, "", "", EPT_SIMPLE, FT_CHAR, static_cast<const void*>( str1.c_str()), str1.size() , true ) );
    
    str1 = "true";
    ptd.push_back( PostTokenData( str1, "", "", EPT_SIMPLE, FT_CHAR, static_cast<const void*>( str1.c_str()), str1.size() , true ) );

    str1 = "&&" ;
    ptd.push_back( PostTokenData( str1, "", "", EPT_SIMPLE, FT_CHAR, static_cast<const void*>( str1.c_str()), str1.size() , true ) );

    str1 = "false";
    ptd.push_back( PostTokenData( str1, "", "", EPT_SIMPLE, FT_CHAR, static_cast<const void*>( str1.c_str()), str1.size() , true ) );
    
    str1 = "||" ;
    ptd.push_back( PostTokenData( str1, "", "", EPT_SIMPLE, FT_CHAR, static_cast<const void*>( str1.c_str()), str1.size() , true ) );
    
    str1 = "true";
    ptd.push_back( PostTokenData( str1, "", "", EPT_SIMPLE, FT_CHAR, static_cast<const void*>( str1.c_str()), str1.size() , true ) );

    
    parse( ptd ) ; ptd.clear() ;
    
    
}

