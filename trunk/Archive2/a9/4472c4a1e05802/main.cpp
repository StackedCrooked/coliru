// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"

#include <utility>
#include <type_traits>
#include <iostream>
#include <sstream>
#include <unordered_map>

namespace TypeTraits
{
    /// Type dependent constant true.
    ///
    /// Use this template if you want to validate that some type expression is valid for given template paramter:
    ///
    ///    template <typename T>
    ///    struct Example<
    ///        T,
    ///        std::enable_if_t<TypeTraits::True<typename T::ExpectedType>::value>
    ///        > : std::true_type
    ///    {};
    ///
    template<typename...>
    struct True : std::true_type
    {
    };

    /// Type dependent constant false.
    ///
    /// Use this template if you want to validate that some type expression is valid for given template paramter:
    ///
    ///    template<typename... TArgs>
    ///    void* Bar(TArgs&&...) const
    ///    {
    ///        static_assert(False<TArgs...>::value, "...");
    ///        return nullptr;
    ///    }
    ///
    template<typename...>
    struct False : std::false_type
    {
    };
}

namespace Serialization
{
    // TODO: Use decltype(auto) when moved to VC13+
    namespace detail
    {
        template <typename TPolicy, typename Enable, typename TValue, typename... TArgs>
        struct ImplementsSerializationPolicy : std::false_type
        {
        };

        template <typename TPolicy, typename TValue, typename... TArgs>
        struct ImplementsSerializationPolicy<
            TPolicy,
            std::enable_if_t<
            TypeTraits::True<typename TPolicy::ImplementsSerializationPolicyTag>::value
            >,
            TValue,
            TArgs...
        > : std::true_type
        {
        };
    } // namespace detail

    template <typename TPolicy, typename TValue, typename... TArgs>
    struct ImplementsSerializationPolicy : detail::ImplementsSerializationPolicy < TPolicy, void, TValue, TArgs... >
    {
    };

    template <typename T>
    struct SerializationPolicy
    {
        using ImplementsSerializationPolicyTag = void;

        template <typename... TArgs>
        void Serialize(TArgs&&...) const
        {
            static_assert(TypeTraits::False<TArgs...>::value, "Provide your own policy. SerializationTests has two ways how to do it.");
            //static_assert(TypeTraits::False<TArgs...>::value, __FUNCSIG__);
        }

        template <typename... TArgs>
        void Deserialize(TArgs&&...) const
        {
            static_assert(TypeTraits::False<TArgs...>::value, "Provide your own policy. SerializationTests has two ways how to do it.");
        }

    };

    // TODO: Use decltype(auto) when moved to VC13+
    template <
        typename TValue,
        typename TPolicy = SerializationPolicy<std::decay_t<TValue>>,
        typename... TArgs,
        typename = std::enable_if_t < ImplementsSerializationPolicy<std::decay_t<TPolicy>, TValue, TArgs...>::value >>
        auto Deserialize(TPolicy&& policy, TArgs&&... args)
        -> decltype(policy.Deserialize(std::forward<TArgs>(args)...))
    {
        return policy.Deserialize(std::forward<TArgs>(args)...);
    }

    // TODO: Use decltype(auto) when moved to VC13+
    template <
        typename TValue,
        typename TPolicy = SerializationPolicy<std::decay_t<TValue>>,
        typename... TArgs,
        typename = std::enable_if_t < !ImplementsSerializationPolicy<std::decay_t<TValue>, TValue, TArgs...>::value >>
        auto Deserialize(TArgs&&... args)
        -> decltype(TPolicy{}.Deserialize(std::forward<TArgs>(args)...))
    {
        return TPolicy{}.Deserialize(std::forward<TArgs>(args)...);
    }

    //// TODO: Use decltype(auto) when moved to VC13+
    //template <
    //    typename TValue,
    //    typename TPolicy = SerializationPolicy<std::decay_t<TValue>>,
    //    typename... TArgs,
    //    typename = std::enable_if_t < ImplementsSerializationPolicy<std::decay_t<TPolicy>, TValue, TArgs...>::value >>
    //    auto Serialize(TPolicy&& policy, TValue&& value, TArgs&&... args)
    //    -> decltype(policy.Serialize(std::forward<TValue>(value), std::forward<TArgs>(args)...))
    //{
    //    return policy.Serialize(std::forward<TValue>(value), std::forward<TArgs>(args)...);
    //}

    //// TODO: Use decltype(auto) when moved to VC13+
    //template <
    //    typename TValue,
    //    typename TPolicy = SerializationPolicy<std::decay_t<TValue>>,
    //    typename... TArgs,
    //    typename = std::enable_if_t < !ImplementsSerializationPolicy<std::decay_t<TValue>, TValue, TArgs...>::value >>
    //    auto Serialize(TValue&& value, TArgs&&... args)
    //    -> decltype(TPolicy{}.Serialize(std::forward<TValue>(value), std::forward<TArgs>(args)...))
    //{
    //    return TPolicy{}.Serialize(std::forward<TValue>(value), std::forward<TArgs>(args)...);
    //}

    // TODO: Use decltype(auto) when moved to VC13+
    template <
        typename TValue,
        typename TPolicy = SerializationPolicy<std::decay_t<TValue>>,
        typename... TArgs,
        typename = std::enable_if_t < ImplementsSerializationPolicy<std::decay_t<TPolicy>, TValue, TArgs...>::value >>
        auto Serialize(TPolicy&& policy, TValue&& value, TArgs&&... args)
        -> decltype(policy.Serialize(std::forward<TValue>(value), std::forward<TArgs>(args)...))
    {
        return policy.Serialize(std::forward<TValue>(value), std::forward<TArgs>(args)...);
    }

    // TODO: Use decltype(auto) when moved to VC13+
    template <
        typename TValue,
        typename TPolicy = SerializationPolicy<std::decay_t<TValue>>,
        typename... TArgs,
        typename = std::enable_if_t < !ImplementsSerializationPolicy<std::decay_t<TValue>, TValue, TArgs...>::value >>
        auto Serialize(TValue&& value, TArgs&&... args)
        -> decltype(TPolicy{}.Serialize(std::forward<TValue>(value), std::forward<TArgs>(args)...))
    {
        return TPolicy{}.Serialize(std::forward<TValue>(value), std::forward<TArgs>(args)...);
    }

    template <typename TValue, typename TPolicy, typename... TArgs, typename TTest = ImplementsSerializationPolicy<std::decay_t<TPolicy>, TValue, TArgs...>>
    void Foo(TPolicy&& , TValue&& , TArgs&&... )
    {
        //static_assert(TTest::value, __FUNCSIG__);
        static_assert(TTest::value, "Foo not working");
    }


    template <typename TValue, typename TPolicy, typename... TArgs, typename TTest = ImplementsSerializationPolicy<std::decay_t<TPolicy>, TValue, TArgs...>>
    void Bar(TPolicy&&, TArgs&&...)
    {
        //static_assert(TTest::value, __FUNCSIG__);
        static_assert(TTest::value, "Bar not working");
    }

}// namespace Serialization


namespace Test
{
    struct A
    {
        A(int v = 0)
            : value(v)
        {
        }

        int value;
    };

    void SerializeA(std::ostream& out, A const& a)
    {
        out << "A::value[" << a.value << "]";
    }

    A DeserializeA(std::istream& in)
    {
        A result{};
        in >> result.value;
        return result;
    }

    /// Define your own custom serialization policy for class \see A.
    struct ASerializationPolicy
    {
        /// Define this tag so this class could be detected by \see ImplementsSerializationPolicy.
        using ImplementsSerializationPolicyTag = void;

        std::string Serialize(A const& a, int i = 0) const
        {
            std::ostringstream out{};
            SerializeA(out, a);
            out << ", ASerializationPolicy::i[" << i << "]";
            return out.str();
        }

        A Deserialize(std::string const& str) const
        {
            std::istringstream input{"1" + str};
            return DeserializeA(input);
        }
    };


    enum class MethodId
    {
        Default = 0,
        GenericSerialize,
        GenericConstSerialize,
        GenericDeserialize,
        GenericConstDeserialize,
        ConstCharDeserialize,
        ConstStringDeserialize,
    };

    std::ostream& operator<<(std::ostream& out, MethodId id)
    {
        //static std::unordered_map<MethodId, std::string const> const s_mapping
        //{
        //    {MethodId::Default, "Default"},
        //    {MethodId::GenericSerialize, "GenericSerialize"},
        //    {MethodId::GenericConstSerialize, "GenericConstSerialize"},
        //    {MethodId::GenericDeserialize, "GenericDeserialize"},
        //    {MethodId::GenericConstDeserialize, "GenericConstDeserialize"},
        //    {MethodId::ConstCharDeserialize, "ConstCharDeserialize"},
        //    {MethodId::ConstStringDeserialize, "ConstStringDeserialize"},
        //};

        return out << "[MethodId,[" <<
            //s_mapping.at(id)
            (int)id
            << "]]";
    }

    struct B
    {
        B(MethodId v = MethodId::Default)
            : value(v)
        {
        }

        MethodId value;
    };

    /// Custom SerializationPolicy to demonstrate overload behaviors
    template <typename TValue>
    struct DemoPolicy
    {
        using ImplementsSerializationPolicyTag = void;

        template<typename... TArgs>
        MethodId Serialize(TArgs&&...) const
        {
            return MethodId::GenericConstSerialize;
        }

        template<typename... TArgs>
        MethodId Serialize(TArgs&&...)
        {
            return MethodId::GenericSerialize;
        }

        template<typename... TArgs>
        TValue Deserialize(TArgs&&...) const
        {
            return MethodId::GenericConstDeserialize;
        }

        template<typename... TArgs>
        TValue Deserialize(TArgs&&...)
        {
            return MethodId::GenericDeserialize;
        }

        TValue Deserialize(std::string const&) const
        {
            return MethodId::ConstStringDeserialize;
        }
    };
}

namespace Serialization
{
    /// Specialize the default policy class for your custom type.
    template<>
    struct SerializationPolicy < Test::A >
    {

        std::string Serialize(Test::A const& a, int i = 0) const
        {
            std::ostringstream out{};
            Test::SerializeA(out, a);
            out << ", SerializationPolicy::i[" << i << "]";
            return out.str();
        }

        Test::A Deserialize(std::string const& str) const
        {
            std::istringstream input{str};
            return Test::DeserializeA(input);
        }

    };

    /// To demonstrate alternative approach, specialize \see ImplementsSerializationPolicy rather than providing the  ImplementsSerializationPolicyTag in the policy.
    template<typename TValue, typename... TArgs>
    struct ImplementsSerializationPolicy<
        SerializationPolicy<Test::A>,
        TValue,
        TArgs...> : 
        std::conditional_t<std::is_same<std::decay_t<TValue>, Test::A>::value, std::true_type, std::false_type>{};
}

int main()
{
    std::cout << "Hello" << std::endl;
    {
        using namespace Serialization;

        {
            using namespace Test;

            std::cout << "Policy: ImplementsSerializationPolicy<SerializationPolicy<A>, A>::value <" << ImplementsSerializationPolicy<SerializationPolicy<A>, A>::value << std::endl;
            std::cout << "Policy: ImplementsSerializationPolicy<SerializationPolicy<A>, B>::value <" << ImplementsSerializationPolicy<SerializationPolicy<A>, B>::value << std::endl;
            std::cout << "Policy: ImplementsSerializationPolicy<SerializationPolicy<B>, B>::value <" << ImplementsSerializationPolicy<SerializationPolicy<B>, B>::value << std::endl;
            std::cout << "Policy: ImplementsSerializationPolicy<DemoPolicy<A>, A>::value <" << ImplementsSerializationPolicy<DemoPolicy<A>, A>::value << std::endl;
            std::cout << "Policy: ImplementsSerializationPolicy<DemoPolicy<A>, B>::value <" << ImplementsSerializationPolicy<DemoPolicy<A>, B>::value << std::endl;
            std::cout << "Policy: ImplementsSerializationPolicy<DemoPolicy<B>, B>::value <" << ImplementsSerializationPolicy<DemoPolicy<B>, B>::value << std::endl;
            std::cout << "Policy: ImplementsSerializationPolicy<ASerializationPolicy, A>::value <" << ImplementsSerializationPolicy<ASerializationPolicy, A>::value << std::endl;
            std::cout << "Policy: ImplementsSerializationPolicy<ASerializationPolicy, B>::value <" << ImplementsSerializationPolicy<ASerializationPolicy, B>::value << std::endl;
        }

        //BOOST_AUTO_TEST_CASE(DefaultPolicySerialize)
        {
            using namespace Test;
            A a{1};
            {
                std::string const expected{"A::value[1], SerializationPolicy::i[0]"};
                auto actual = Serialize(a);
                std::cout << __LINE__ << " : "  << (expected == actual) << std::endl;
            }
          {
              std::string const expected{"A::value[1], SerializationPolicy::i[1]"};
              auto actual = Serialize(a, 1);
              std::cout << __LINE__ << " : "  << (expected == actual) << std::endl;
          }
        }

        //BOOST_AUTO_TEST_CASE(DefaultPolicyDeserialize)
      {
          using namespace Test;
          auto const& actual = Deserialize<A>("1");
          std::cout << __LINE__ << " : "  << (1 == actual.value) << std::endl;
      }

      //BOOST_AUTO_TEST_CASE(ExplicitPolicySerialize)
      {
          using namespace Test;
          A a{1};
          {
              std::string const expected{"A::value[1], ASerializationPolicy::i[0]"};
              auto actual = Serialize(ASerializationPolicy{}, a);//Passing policy as rvalue ref.
              std::cout << __LINE__ << " : "  << (expected == actual) << std::endl;
          }
          {
              std::string const expected{"A::value[1], ASerializationPolicy::i[1]"};
              auto const& policy = ASerializationPolicy{};//Passing policy as const lvalue ref.
              auto actual = Serialize(policy, a, 1);
              std::cout << __LINE__ << " : "  << (expected == actual) << std::endl;
          }
          {

              std::string const expected{"A::value[1], SerializationPolicy::i[0]"};
              Foo(SerializationPolicy < A > {}, a);
              //(void) Serialize(SerializationPolicy < A > {}, a);//Passing policy as rvalue ref.
              auto actual = Serialize(SerializationPolicy < A > {}, a);//Passing policy as rvalue ref.
              std::cout << __LINE__ << " : "  << (expected == actual) << std::endl;
          }
          {
              std::string const expected{"A::value[1], SerializationPolicy::i[0]"};
              Foo(SerializationPolicy < B > {}, B{});
              //(void) Serialize(SerializationPolicy < B > {}, a);//Passing policy as rvalue ref.
              //auto actual = Serialize(SerializationPolicy < B > {}, B{});//Passing policy as rvalue ref.
              //std::cout << __LINE__ << " : " << (expected == actual) << std::endl;
          }
      }

      //BOOST_AUTO_TEST_CASE(ExplicitPolicyDeserialize)
      {
          using namespace Test;
          {
              auto const& actual = Deserialize<A>(ASerializationPolicy{}, "1");
              std::cout << __LINE__ << " : "  << (11 == actual.value) << std::endl;
          }
          {
              auto const& actual = Deserialize<A>(SerializationPolicy < A > {}, "1");
              Bar<A>(SerializationPolicy < A > {}, "1");
              std::cout << __LINE__ << " : "  << (1 == actual.value) << std::endl;
          }
      }

      {

          //BOOST_AUTO_TEST_CASE(GenericSerialize)
          {
              using namespace Test;
              auto policy = Test::DemoPolicy<Test::B>();
              //(void)Serialize(B{});//static_assert error (trying to use the unspecialized default policy)
              //"class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > __cdecl Test::DemoPolicy<struct Test::B>::Serialize<struct Test::B>(struct Test::B &&)",
              auto value = Serialize(policy, B{});
              std::cout << __LINE__ << " : "  << (MethodId::GenericSerialize == value) << std::endl;
          }

          //BOOST_AUTO_TEST_CASE(GenericConstSerialize)
        {
            using namespace Test;
            auto const& c_policy = Test::DemoPolicy<Test::B>();
            B b{};
            //"class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > __cdecl Test::DemoPolicy<struct Test::B>::Serialize<structTest::B&>(struct Test::B &) const",
            auto value = Serialize(c_policy, b);
            std::cout << __LINE__ << " : "  << (MethodId::GenericConstSerialize == value) << std::endl;
        }

        //BOOST_AUTO_TEST_CASE(GenericConstDeserialize)
        {
            using namespace Test;
            auto const& c_policy = Test::DemoPolicy<Test::B>();
            //Notice that in this case the compiler did call the GenericConstDeserialize instead of ConstStringDeserialize.
            //If we remove the GenericConstDeserialize method, the compiler will do the implicit conversion and it will call ConstStringDeserialize.
            //"struct Test::B __cdecl Test::DemoPolicy<struct Test::B>::Deserialize<const char(&)[2]>(const char (&)[2]) const"
            auto b = Deserialize<B>(c_policy, "1");
            std::cout << __LINE__ << " : "  << (MethodId::GenericConstDeserialize == b.value) << std::endl;
        }

        //BOOST_AUTO_TEST_CASE(ConstStringDeserialize)
        {
            using namespace Test;
            std::string const& str = "1";
            auto const& c_policy = Test::DemoPolicy<Test::B>();
            //"struct Test::B __cdecl Test::DemoPolicy<struct Test::B>::Deserialize(const class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > &) const",
            auto b = Deserialize<B>(c_policy, str);
            std::cout << __LINE__ << " : "  << (MethodId::ConstStringDeserialize == b.value) << std::endl;
        }

      }

    }

}

//int _tmain(int argc, _TCHAR* argv[])
//{
//    return 0;
//}

