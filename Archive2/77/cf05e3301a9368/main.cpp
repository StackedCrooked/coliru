/// Assertions

#define pa_false false
#define I2E_OVERRIDE override

#include <exception>
#include <utility>
#include <sstream>

#include <iostream>

namespace ling{
    namespace assert{
        struct Handler{
            struct Params{
                const std::string& condition;
                const std::string& file;
                size_t line;
                const std::string& message;
            };
            using Type = void (*)(Params);
            enum class availableHandlers {abort, throwException};
            
            struct Failure : public std::exception{
                Failure(const std::string& message) : message(message) {}
                const char* what() const noexcept I2E_OVERRIDE;
                private:
                std::string message;
            };
            
            static void invoke(const std::string& text, const std::string& file, size_t line, const std::string& message);
            static void setHandler(Type handler);
            static void setHandler(availableHandlers handler = availableHandlers::abort);
            
            private:
            static Handler& instance(){
                static Handler obj;
                return obj;
            }
            
            private:
            Handler() : currentHandler(abortHandler) {}
            Handler(const Handler&);
            Handler& operator=(const Handler&);
            
            static void abortHandler(Params p);
            static void throwHandler(Params p);
            
            Type currentHandler;
        };
        
        
        template <typename List>
        struct FormatData{
            using type = List;
            List list;
        };
        
        struct None{};
        
        template <typename Begin, typename Value>
        FormatData<std::pair<Begin&&, Value&&>> operator<<(FormatData<Begin>&& begin, Value&& value) noexcept {
            return {{ std::forward<Begin>(begin.list), std::forward<Value>(value) }};
        }
        
        using PfnManipulator = std::ostream& (*)(std::ostream&);
        
        template <typename Begin>
        FormatData<std::pair<Begin&&, PfnManipulator>> operator<<(FormatData<Begin>&& begin, PfnManipulator pfn) noexcept {
            return {{ std::forward<Begin>(begin.list), pfn }};
        }
        
        template <typename Begin, size_t n>
        FormatData<std::pair<Begin&&, const char*>> operator<<(FormatData<Begin>&& begin, const char(&sz)[n]) noexcept {
            return {{ std::forward<Begin>(begin.list), sz }};
        }
        
        template <typename TFormatDataPair>
        void FormatRecursive(std::ostream& os, TFormatDataPair&& data) noexcept {
            FormatRecursive(os, std::forward<typename TFormatDataPair::first_type>(data.first));
            os << std::forward<typename TFormatDataPair::second_type>(data.second);
        }
        
        inline void FormatRecursive(std::ostream& os, None) noexcept {}
        
        template <typename TFormatData>
        std::string Format(TFormatData&& data) noexcept {
            std::ostringstream ss;
            FormatRecursive(ss, std::forward<typename TFormatData::type>(data.list));
            return ss.str();
        }
    }   
}

#define FORMAT(...) ling::assert::Format(ling::assert::FormatData<ling::assert::None>{} << __VA_ARGS__)

#define LING_ASSERT_ASSERT(condition, message) do{ \
    if(!(condition)){ \
        ling::assert::Handler::invoke(#condition, __FILE__, __LINE__, message); \
    } \
} while(pa_false)

#define LING_ASSERT_CODE_EXECUTE(...) do{ \
__VA_ARGS__; \
} while(pa_false)

#define LING_ASSERT_CODE_DONT_EXECUTE(...) do{(void) sizeof (__VA_ARGS__);}while(pa_false)


#if defined(LING_ASSERT_ENABLED)
#define LING_ASSERT_OPT_ENABLED
#endif

#if defined(LING_ASSERT_SAFE_ENABLED)
#define LING_ASSERT_ENABLED
#define LING_ASSERT_OPT_ENABLED
#endif

#if defined(LING_ASSERT_OPT_ENABLED)
#define LING_ASSERT_OPT(condition) LING_ASSERT_ASSERT(condition, "")
#define LING_ASSERT_OPT_MESSAGE(condition, message) LING_ASSERT_ASSERT(condition, FORMAT(message))
#define LING_ASSERT_OPT_CODE(...) LING_ASSERT_CODE_EXECUTE(__VA_ARGS__)
#else
#define LING_ASSERT_OPT(condition) do{(void) sizeof (condition);}while(pa_false)
#define LING_ASSERT_OPT_MESSAGE(condition, message) do{(void) sizeof (condition); (void) sizeof (FORMAT(message));}while(pa_false)
#define LING_ASSERT_OPT_CODE(...) LING_ASSERT_CODE_DONT_EXECUTE(__VA_ARGS__)
#endif

#if defined(LING_ASSERT_ENABLED)
#define LING_ASSERT(condition) LING_ASSERT_ASSERT(condition, "")
#define LING_ASSERT_MESSAGE(condition, message) LING_ASSERT_ASSERT(condition, FORMAT(message))
#define LING_ASSERT_CODE(...) LING_ASSERT_CODE_EXECUTE(__VA_ARGS__)
#else
#define LING_ASSERT(condition) do{(void) sizeof (condition);}while(pa_false)
#define LING_ASSERT_MESSAGE(condition, message) do{(void) sizeof (condition); (void) sizeof (FORMAT(message));}while(pa_false)
#define LING_ASSERT_CODE(...) LING_ASSERT_CODE_DONT_EXECUTE(__VA_ARGS__)
#endif

#if defined(LING_ASSERT_SAFE_ENABLED)
#define LING_ASSERT_SAFE(condition) LING_ASSERT_ASSERT(condition, "")
#define LING_ASSERT_SAFE_MESSAGE(condition, message) LING_ASSERT_ASSERT(condition, FORMAT(message))
#define LING_ASSERT_SAFE_CODE(...) LING_ASSERT_CODE_EXECUTE(__VA_ARGS__)
#else
#define LING_ASSERT_SAFE(condition) do{(void) sizeof (condition);}while(pa_false)
#define LING_ASSERT_SAFE_MESSAGE(condition, message) do{(void) sizeof (condition); (void) sizeof (FORMAT(message));}while(pa_false)
#define LING_ASSERT_SAFE_CODE(...) LING_ASSERT_CODE_DONT_EXECUTE(__VA_ARGS__)
#endif

namespace ling{
    namespace assert{
        void Handler::setHandler(availableHandlers handler){
            switch(handler){
                case availableHandlers::throwException:
                instance().currentHandler = throwHandler;
                break;
                case availableHandlers::abort:
                default:
                instance().currentHandler = abortHandler;
            }
        }
        void Handler::invoke(const std::string& text, const std::string& file, size_t line, const std::string& message){
            instance().currentHandler(Params{text, file, line, message});
        }
        void Handler::setHandler(Type handler){
            instance().currentHandler = handler;
        }
        void Handler::abortHandler(Params p){
            if(!p.message.empty()){
                std::cout << p.message << " (";
            }
            std::cout << "assertion failed: \"" << p.condition << "\" is false in " << p.file << " @ " << p.line;
            if(!p.message.empty()){
                std::cout << ')';
            }
            std::cout << std::endl;
            abort();
        }
        void Handler::throwHandler(Params p){
            std::ostringstream ss;
            if(!p.message.empty()){
                ss << p.message << " (";
            }
            ss << "assertion failed: \"" << p.condition << "\" is false in " << p.file << " @ " << p.line;
            if(!p.message.empty()){
                ss << ')';
            }
            throw Failure{ss.str()};
        }
        
        const char* Handler::Failure::what() const noexcept {
            return message.c_str();
        }
    }
}

int main(){    
    using ling::assert::Handler;
    Handler::setHandler(Handler::availableHandlers::throwException);
   
    auto normal = true;
    LING_ASSERT_CODE(normal = false);
    LING_ASSERT_MESSAGE(normal, 'F' << normal << "**" << "k");
    
    auto opt = true;
    LING_ASSERT_OPT_CODE(opt = false);
    LING_ASSERT_OPT(opt);
}
