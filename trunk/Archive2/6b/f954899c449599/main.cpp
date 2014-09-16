#include <type_traits>
#include <memory>

class CDelegateCore {};

class CDelegate : public CDelegateCore {};

class CEvent
{
   private:

      /// Simple empty enumeration used for enable_if test.
      enum class enabler_t {};

      template<typename T>
      using EnableIf = typename std::enable_if<T::value, enabler_t>::type;

   public:

      CEvent() {}
      ~CEvent() {}

      void operator += (CDelegateCore* func) {}

      template<typename T, typename Deleter>
      std::enable_if_t<std::is_base_of<CDelegateCore, T>::value>
       operator += (std::unique_ptr<T, Deleter> const& func) { *this += func.get(); }
};

int main()
{
    std::unique_ptr<CDelegate> testdel;
    // ... initialize testdel ...

    CEvent EVENT;
    EVENT += testdel;
}
