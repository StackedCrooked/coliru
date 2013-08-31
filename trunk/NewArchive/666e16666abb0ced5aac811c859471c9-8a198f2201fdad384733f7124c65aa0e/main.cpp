#include <iostream>
#include <string>
#include <map>
#include <mutex>
#include <memory>
#include <stdexcept>

enum class Utterances {
    hello = 6300,
    world = 6301 
    // RESERVED RANGE: 10000 - 65535 (reserved for dynamically loaded utterances)
};

enum class CapitalizationPolicy
{
    Uppercase,
    Lowercase,
    Titlecase
};

template <typename Derived>
class GenericSingletonBase 
{
    protected: 
        GenericSingletonBase() {}
        ~GenericSingletonBase() {}
    public:
        static Derived& instance()
        {
            static Derived theInstance;
            return theInstance;
        }
};

template <typename T>
class IGeneralPolicyApplication
{
    public:
        virtual ~IGeneralPolicyApplication() { }
        virtual void Apply(T& target) const = 0;
};

class ICapitalizationPolicyImplBase : IGeneralPolicyApplication<std::string>
{
    public:
        virtual ~ICapitalizationPolicyImplBase() { }
};

class UppercaseCapitalizationPolicyImplementation : public ICapitalizationPolicyImplBase
{
    public:
        virtual void Apply(std::string& target) const
        {
            for (auto& ch : target)
                ch = std::toupper((int)(unsigned int) ch);
        }
};

class LowercaseCapitalizationPolicyImplementation : public ICapitalizationPolicyImplBase
{
    public:
        virtual void Apply(std::string& target) const
        {
            for (auto& ch : target)
                ch = std::tolower((int)(unsigned int) ch);
        }
};

class TitlecaseCapitalizationPolicyImplementation : public ICapitalizationPolicyImplBase
{
    public:
        virtual void Apply(std::string& target) const
        {
            for (auto& ch : target)
                ch = std::tolower((int)(unsigned int) ch);
            for (auto& ch : target)
            {
                if (std::isspace((int)(unsigned int) ch))
                    continue;
                ch = std::toupper((int)(unsigned) ch);
                break;
            }
        }
};

class CapitalizationPolicyFactory : public GenericSingletonBase<CapitalizationPolicyFactory>
{
    private:
        CapitalizationPolicyFactory() {}
        friend class GenericSingletonBase<CapitalizationPolicyFactory>;
    public:
        std::unique_ptr<ICapitalizationPolicyImplBase> Create(CapitalizationPolicy policy)
        {
            switch (policy)
            {
                case CapitalizationPolicy::Uppercase:
                    return std::unique_ptr<ICapitalizationPolicyImplBase>(new UppercaseCapitalizationPolicyImplementation());
                case CapitalizationPolicy::Lowercase:
                    return std::unique_ptr<ICapitalizationPolicyImplBase>(new LowercaseCapitalizationPolicyImplementation());
                case CapitalizationPolicy::Titlecase:
                    return std::unique_ptr<ICapitalizationPolicyImplBase>(new TitlecaseCapitalizationPolicyImplementation());
                default:
                    throw new std::runtime_error("CapitalizationPolicyFactory: unable to instantiate requested CapitalizationPolicy instance");
            }
        }
};

class IUtteranceProvider
{
  public:
    virtual std::string makeWord() const = 0;
  protected:
    virtual ~IUtteranceProvider() {}
    friend class UtteranceProviderFactory;
};

class LocalizedWordUtteranceProviderImplementation : public IUtteranceProvider
{
    std::string word;
    virtual std::string makeWord() const
    {
        return word;
    }
    virtual ~LocalizedWordUtteranceProviderImplementation() { }
  private:
    LocalizedWordUtteranceProviderImplementation(std::string aword): word(aword) {}
    friend class UtteranceProviderFactory;
};

class UtteranceProviderFactory : public GenericSingletonBase<UtteranceProviderFactory>
{
private:
    std::map<Utterances, std::shared_ptr<IUtteranceProvider>> _registered;
    UtteranceProviderFactory() { }
    friend class GenericSingletonBase<UtteranceProviderFactory>;
public:
    bool registerUtterance(Utterances utterance, std::string localizedResource)
    {
        auto createResource = instantiateLocalizedWordUtteranceProviderImplementation(localizedResource);

        std::shared_ptr<IUtteranceProvider> utteranceProvider(createResource, &destroyLocalizedWordUtteranceProviderImplementation);

        auto tryInsert = _registered.insert(std::make_pair(utterance, utteranceProvider));
        return tryInsert.second;
    }
private:
    // only UtteranceProviderFactory has permission to create/destroy concrete IUtteranceProvider instances
    static void destroyLocalizedWordUtteranceProviderImplementation(IUtteranceProvider* rawptr)
    {
        delete rawptr;
    }
    static IUtteranceProvider* instantiateLocalizedWordUtteranceProviderImplementation(std::string localizedResource)
    {
        return new LocalizedWordUtteranceProviderImplementation(localizedResource);
    }
};

int main()
{
    UtteranceProviderFactory::instance().registerUtterance(Utterances::hello, "hello");
    UtteranceProviderFactory::instance().registerUtterance(Utterances::hello, "world");
     // EXERCISE: implement ProgrammersCreedOutputEngine using UtteranceProviderFactory and CapitalizationPolicyFactory
     //
     // for bonus pounts: make the capitalization strategy configurable from a .properties file, or an XML configuration file
}
