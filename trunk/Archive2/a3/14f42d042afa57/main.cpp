#include <iostream>
#include <type_traits>
#include <initializer_list>
#include <limits>
#include <climits>

using namespace std;

//Just some forward decl's
template <template <typename... Fields> class HostType, typename... Fields>
struct const_obj;

template <typename Field, typename... Fields>
class pack_field_list;

template <template <typename... Fields> class HostType, unsigned int indexToModify, unsigned int currentIndex, typename ValueType, ValueType newValue, typename Field, typename... Fields>
class modify_field;

template <unsigned int index, unsigned int currentIndex, typename Field, typename... Fields>
class get_field_type;

//---------------------------------------------------------------
// Basic Field Type
//---------------------------------------------------------------
template <typename ValueType, ValueType _value>
struct field
{
    typedef ValueType value_type;
    static const ValueType value = _value;
};


//---------------------------------------------------------------
// Storage of the fields as an array of unsigned chars
//---------------------------------------------------------------
template <unsigned char... uchars>
struct packed_storage
{
    constexpr packed_storage() : data{uchars...} {}
    const unsigned char data[sizeof...(uchars)]; 
};


//---------------------------------------------------------------
// Template metaprograms that act on a Field list
//---------------------------------------------------------------

//Metaprogram to convert an individual field into unsigned char data
template <typename Field, typename... Fields>
class pack_field
{
    template <unsigned int K, bool lastField, unsigned char... uchars>
    struct pack_field_impl
    {
        typedef typename pack_field_impl<K-1, lastField, uchars..., (unsigned char)(Field::value >> ((K-1) * CHAR_BIT))>::result result;
    };
    
    template <bool lastField, unsigned char... uchars>
    struct pack_field_impl<0, lastField, uchars...>
    {
        typedef typename pack_field_list<Fields...>::template result<uchars...> result;
    };
    
    template <unsigned char... uchars>
    struct pack_field_impl<0, true, uchars...>
    {
         typedef packed_storage<uchars...> result;
    };
    
public:
    template <unsigned char... uchars>
    using result = typename pack_field_impl<sizeof(typename Field::value_type), sizeof...(Fields) == 0, uchars...>::result;
};

//Metaprogram to pack a whole field list into unsigned char data (makes use of pack_field)
template <typename Field, typename... Fields>
class pack_field_list
{
    template <unsigned char... uchars>
    struct pack_field_list_impl
    {
        typedef typename pack_field<Field, Fields...>::template result<uchars...> result; 
    };
    
public:
        
    template <unsigned char... uchars>
    using result = typename pack_field_list_impl<uchars...>::result;
};

//Metaprogram to modify a field in a field list
template <template <typename... Fields> class HostType, unsigned int indexToModify, unsigned int currentIndex, typename ValueType, ValueType newValue, typename Field, typename... Fields>
class modify_field
{   
    template <bool mustModify, ValueType value>
    struct get_value_impl
    {
        typedef Field result;
    };
    
    template <ValueType value>
    struct get_value_impl<true, value>
    {
        typedef field<typename Field::value_type, value> result;
    };
    
    template <bool lastField, bool mustModify, typename... NewFields>
    struct modify_field_impl
    {
        typedef typename modify_field<HostType, indexToModify, currentIndex + 1, ValueType, newValue, Fields...>::template result<NewFields..., typename get_value_impl<mustModify, newValue>::result> result;
    };
    
    template <bool mustModify, typename... NewFields>
    struct modify_field_impl<true, mustModify, NewFields...>
    {
        //typedef const_obj<HostType, NewFields..., typename get_value_impl<mustModify, newValue>::result> result;
        typedef HostType<NewFields..., typename get_value_impl<mustModify, newValue>::result> result;
    };
    
public:

    template <typename... NewFields>
    using result = typename modify_field_impl<sizeof...(Fields) == 0, indexToModify == currentIndex, NewFields...>::result;
};


//Metaprogram to get the type of a given field of a field list
template <unsigned int index, unsigned int currentIndex, typename Field, typename... Fields>
class get_field_type
{
    template <bool getThisType, typename CurrentField>
    struct get_field_type_impl
    {
        typedef typename get_field_type<index, currentIndex + 1, Fields...>::result result;
    };
    
    template <typename CurrentField>
    struct get_field_type_impl<true, CurrentField>
    {
        typedef typename CurrentField::value_type result;
    };
    
public:
    typedef typename get_field_type_impl<index == currentIndex, Field>::result result;
};

//Metaprogram to get the value of a given field of a field list
template <unsigned int index, unsigned int currentIndex, typename Field, typename... Fields>
class get_field_value
{
    template <bool getThisValue, typename CurrentField>
    struct get_field_value_impl
    {
        enum
        {
            result = get_field_value<index, currentIndex + 1, Fields...>::result
        };
    };
    
    template <typename CurrentField>
    struct get_field_value_impl<true, CurrentField>
    {
        enum
        {
            result = CurrentField::value
        };
    };
    
public:
    enum
    {
        result = get_field_value_impl<index == currentIndex, Field>::result 
    };
};


//---------------------------------------------------------------
// Main const_obj template (derive from this to create your classes)
//---------------------------------------------------------------
template <template <typename... Fields> class HostType, typename... Fields>
struct const_obj : public pack_field_list<Fields...>::template result<>
{
    constexpr const_obj() {}
    
    template <unsigned int K, typename get_field_type<K, 0, Fields...>::result newValue>
    using Set = typename modify_field<HostType, K, 0, typename get_field_type<K, 0, Fields...>::result, newValue, Fields...>::template result<>;
    
    template <unsigned int K>
    constexpr typename get_field_type<K, 0, Fields...>::result Get() const
    {
        return get_field_value<K, 0, Fields...>::result;
    }
};


//---------------------------------------------------------------
// Example of a solid data structure
//---------------------------------------------------------------

template <
    //Declare your fields here, with types and default values
    typename PortNumber = field<int, 100>, 
    typename PortLetter = field<char, 'A'>
>
struct MyStruct : public const_obj<MyStruct, PortNumber, PortLetter>  //Derive from const_obj like this, passing the name of your class + all field names as parameters
{
    //Your setters have to be declared like this, by calling the Set<> template provided by the base class
    //The compiler needs to be told that Set is part of MyStruct, probably because const_obj has not been instantiated at this point
    //in the parsing so it doesn't know what members it has. The result is that you have to use the weird 'typename MyStruct::template Set<>' syntax
    //You need to provide the 0-based index of the field that holds the corresponding value
    template<int portNumber>
    using SetPortNumber = typename MyStruct::template Set<0, portNumber>;
    
    template<int portLetter>
    using SetPortLetter = typename MyStruct::template Set<1, portLetter>;
    
    template<int portNumber, char portLetter>
    using SetPort = typename MyStruct::template Set<0, portNumber>::
                             MyStruct::template Set<1, portLetter>;
    
    
    //You getters, if you want them, can be declared like this
    constexpr int GetPortNumber() const
    {
        return MyStruct::template Get<0>();
    }
    
    constexpr char GetPortLetter() const
    {
        return MyStruct::template Get<1>();
    }
};

int main()
{
    //Compile-time generation of the type
    constexpr auto myObject = 
        MyStruct<>
        ::SetPortNumber<150>
        ::SetPortLetter<'Z'>();
    
    cout << myObject.GetPortNumber() << endl;
    cout << myObject.GetPortLetter() << endl;
}

