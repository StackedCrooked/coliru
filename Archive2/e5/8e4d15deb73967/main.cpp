#include <iostream>
#include <type_traits>

namespace {
    
  namespace detail {
      static constexpr size_t IllegalIndex = ~(0u);
      
      template <size_t CurrentIndex, size_t DesiredIndex, typename TCaseList>
      struct SelectBool {
          static constexpr bool Value = (CurrentIndex == 0) ? TCaseList::Value : SelectBool<CurrentIndex - 1, DesiredIndex - 1, typename TCaseList::Next>::Value;
      };
      
      template <size_t DesiredIndex, typename TCaseList>
      struct SelectBool<0, DesiredIndex, TCaseList> {
          static constexpr bool Value = (DesiredIndex == 0) ? TCaseList::Value : false;
      };
      
      
      template <size_t CurrentIndex, typename TCaseList>
      struct SelectBool<CurrentIndex, IllegalIndex, TCaseList> {
          static constexpr bool Value = false;
      };
      
      // Given a TCaseList<bool...> select the DesiredIndex-nth value from the list. If DesiredIndex is out of range, returns false.
      template <size_t DesiredIndex, typename TCaseList>
      struct SelectBoolFromList {
          static constexpr bool Value = SelectBool<DesiredIndex, DesiredIndex, TCaseList>::Value;
      };
      
      template <size_t CurrentIndex, size_t DesiredIndex, typename TCaseList>
      struct OrBoolListUpToImpl {
          static constexpr bool _ThisValue =  TCaseList::Value;
          static constexpr bool Value = _ThisValue || ((CurrentIndex == 0) ? false : OrBoolListUpToImpl<CurrentIndex - 1, DesiredIndex - 1, typename TCaseList::Next>::Value);
      };
      
      template <size_t DesiredIndex, typename TCaseList>
      struct OrBoolListUpToImpl<0, DesiredIndex, TCaseList> {
          static constexpr bool Value = (DesiredIndex == 0) ? TCaseList::Value : false;
      };
      
      template <size_t CurrentIndex, typename TCaseList>
      struct OrBoolListUpToImpl<CurrentIndex, IllegalIndex, TCaseList> {
          static constexpr bool Value = false;
      };
      
      // Given a TCaseList<bool...> perform a logical OR operation on the range [0, DesiredIndex]. If DesiredIndex is out of range, returns false.
      template <size_t DesiredIndex, typename TCaseList>
      struct OrBoolListUpTo {
        static constexpr bool Value = OrBoolListUpToImpl<DesiredIndex, DesiredIndex, TCaseList>::Value;  
      };
      
      template <bool LowerPriorityEnabled, bool ThisEnabled, typename TType>
      struct EnableSwitchIf : std::enable_if<LowerPriorityEnabled ? false : ThisEnabled, TType> {
          static constexpr bool _LowerPriorityEnabled = LowerPriorityEnabled;
          static constexpr bool _ThisEnabled = ThisEnabled;
      };
     
      template <size_t DesiredIndex, typename TCaseList, typename TType>
      struct EnableSwitch : EnableSwitchIf<detail::OrBoolListUpTo<DesiredIndex - 1, TCaseList>::Value, // Lower Priority Enabled?
                                           detail::SelectBoolFromList<DesiredIndex, TCaseList>::Value,   // This one is enabled?
                                           TType> {};

      template <typename TCaseList, typename TType>
      struct EnableSwitch<0, TCaseList, TType> : EnableSwitchIf<false, // Lower priority is not enabled.
                                                                detail::SelectBoolFromList<0, TCaseList>::Value, // Check if this value only is enabled
                                                                TType>  {
      };
  };
    
  // Use as a SFINAE similar to enable_if.
  // Works as a switch/case statement that we break out of after the first condition is met.
  // For example, if multiple conditions are true only the first one is selected.
  // void do_something (typename EnableSwitch<CaseNumber<#>, CaseList<bool ... Conditions, TType>::type* = 0)
  template <typename TCaseSwitch, typename TCaseList, typename TType = void>
  struct EnableSwitch : detail::EnableSwitch<TCaseSwitch::CaseNumber, TCaseList, TType> {
  };
  
  template <bool ... Conditions>
  struct CaseList {
      static size_t constexpr Size = sizeof...(Conditions);
  };
  
  template <bool Condition, bool ... Conditions>
  struct CaseList<Condition, Conditions ...> {
      static size_t constexpr Size = sizeof...(Conditions) + 1;
      static bool constexpr Value = Condition;
      
      using Next = CaseList<Conditions ...>;
  };
  
  template <size_t kCaseNumber>
  struct CaseSwitch {
      static constexpr size_t CaseNumber = kCaseNumber;
  };
  
  struct CaseDefault : CaseSwitch<detail::IllegalIndex> {
  };
  
  ////
  ////
  ////
  
  template <typename T>
  struct MyCaseList : CaseList<std::is_floating_point<T>::value,
                               std::is_convertible<T, const char*>::value,
                               std::is_pod<T>::value> 
  {};
  
  template <typename T>
  void print_something(const T& value, typename EnableSwitch<CaseSwitch<0>, MyCaseList<T>>::type* = 0) {
      std::cout << "floating point: " << value << std::endl;
  }
  
  template <typename T>
  void print_something(const T& value, typename EnableSwitch<CaseSwitch<1>, MyCaseList<T>>::type* = 0) {
      std::cout << "c string: " << value << std::endl;
  }
  
  template <typename T>
  void print_something(const T& value, typename EnableSwitch<CaseSwitch<2>, MyCaseList<T>>::type* = 0) {
      std::cout << " unknown POD: " << &value << std::endl;   
  }
  
  template <typename T>
  const char* GetTypeName() {
      static const char* f = __PRETTY_FUNCTION__;
      return f;
  }

  
} // namepsace

struct SomePod {
    int x;
};

int main() {
    
    #if 0
    using MyList = CaseList<true, false, true>;
    
    std::cout << detail::SelectBoolFromList<detail::IllegalIndex, MyList>::Value << std::endl;
    std::cout << detail::SelectBoolFromList<0, MyList>::Value << std::endl;
    std::cout << detail::SelectBoolFromList<1, MyList>::Value << std::endl;
    std::cout << detail::SelectBoolFromList<2, MyList>::Value << std::endl;
    
    std::cout << "Or Bool List Up To " << std::endl;
    
    using FalseList2 = CaseList<false, false, true>;
    
    std::cout << detail::OrBoolListUpTo<0, FalseList2>::Value << std::endl;
    std::cout << detail::OrBoolListUpTo<1, FalseList2>::Value << std::endl;
    std::cout << detail::OrBoolListUpTo<2, FalseList2>::Value << std::endl;
    //std::cout << detail::OrBoolListUpTo<1, MyList>::Value << std::endl;
    //std::cout << detail::OrBoolListUpTo<2, MyList>::Value << std::endl;
    
    
    std::cout << "Printed values" << std::endl;
    
    // this works:
    std::cout << "is floating point: " << detail::SelectBoolFromList<0, MyCaseList<float>>::Value << std::endl;
    
    
    std::cout << "is const char a floating point? " << detail::OrBoolListUpTo<1 - 1, MyCaseList<const char*>>::Value << std::endl;
    std::cout << "is const char*: " << detail::SelectBoolFromList<1, MyCaseList<const char*>>::Value << std::endl;
    std::cout << " enabled lower priority: " << EnableSwitch<CaseSwitch<1>, MyCaseList<const char*>>::_LowerPriorityEnabled << std::endl;
    std::cout << " enabled this: " << EnableSwitch<CaseSwitch<1>, MyCaseList<const char*>>::_ThisEnabled << std::endl;
    
    using is_charstar_enabled = EnableSwitch<CaseSwitch<1>, MyCaseList<const char*>>;
    
    std::cout << GetTypeName<is_charstar_enabled>() << std::endl;
    std::cout << GetTypeName<is_charstar_enabled::type>() << std::endl;
    #endif
    
    print_something(1.0f);
    print_something("hello world");
    
    SomePod pod = {5};
    print_something(pod);
    
    return 0;
}