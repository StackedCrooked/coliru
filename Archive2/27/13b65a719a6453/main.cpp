#include <iostream>
#include <memory>
#include <typeindex>
#include <vector>
#include <type_traits>

using namespace std;

// Predefine template delegate factory
template < typename R, typename... Args >
class brGenericDelegate ;

// C++11 template alias to announce functor definition
template < typename R, typename... Args >
using brGenericDelegateType = std::function< std::shared_ptr<R>(Args...) > ;

class brDelegate
{
protected:
    brDelegate(){}

public:
   virtual ~brDelegate() = default ;

    template < typename R, typename... Args >
    static std::shared_ptr<brDelegate> create( typename brGenericDelegate<R,Args...>::functor func )
	{
		return std::make_shared<brGenericDelegate<R,Args...>>(func) ;
	}

    template < typename R, typename... Args >
	std::shared_ptr<R> run( Args... args ) const
    {
        using derived_type = brGenericDelegate<R,Args...> ;
        return dynamic_cast< const derived_type& >(*this)(args...) ;
    }

	template < typename R, typename... ARGS >
	bool isSignatureEquals(void) const
	{
		bool isEquals = false;
		if(this->getReturnType() == typeid(R)){
			if(this->getNumberOfArguments() == sizeof...(ARGS)){
				std::vector<std::type_index> args;
				args.insert(args.end(), {typeid(ARGS)...});
				if(args == this->getArgTypes()){
					isEquals = true;
				}
			}
		}
		return isEquals;
	}

protected:
	virtual std::type_index getReturnType(void) const = 0;
	virtual unsigned int getNumberOfArguments(void) const = 0;
	virtual const std::vector<std::type_index>& getArgTypes(void) const = 0;
};

template < typename R, typename... Args >
class brGenericDelegate : public brDelegate
{
public:
    using functor = brGenericDelegateType< R, Args... >;
    brGenericDelegate( functor f ) : fn(f) {
		m_args.insert(m_args.end(), {typeid(Args)...});
	}

    std::shared_ptr<R> operator() ( Args... args ) const
	{
		return fn(args...) ;
	}

	std::type_index getReturnType(void) const {
		return typeid(R);
	}

	unsigned int getNumberOfArguments(void) const {
		return sizeof...(Args);
	}

	const std::vector<std::type_index>& getArgTypes() const{
		return m_args;
	}

private:
    const functor fn ;
	std::vector<std::type_index> m_args;
};

// Perfect forwarding test function
template <typename R, typename ... ARGS>
std::shared_ptr<R> resolve(ARGS&& ... args)
{
	return nullptr;
}

// Test interface 1
class Gun
{
public:
	Gun(){}
	virtual ~Gun(){}

	virtual std::string getName(void) const = 0;
	virtual std::string getType(void) const = 0;
	virtual double getCaliber(void) const = 0;
};

class MachineGun : virtual public Gun
{
public:
	MachineGun(double caliber, const std::string name)
	:m_caliber(caliber), m_name(name){}
	virtual ~MachineGun(){}

	virtual std::string getName(void) const {
		return m_name;
	}

	virtual std::string getType(void) const {
		return "projectile";
	}

	virtual double getCaliber(void) const {
		return m_caliber;
	}

private:
    double m_caliber;
	std::string m_name;
};

class Armament
{
public:
	Armament(std::shared_ptr<Gun> primary)
	:m_primary(primary){}
	~Armament(){}

	const std::shared_ptr<Gun> getPrimaryWeapon(void){
		return m_primary;
	}

	const std::shared_ptr<Gun> getSecondaryWeapon(void){
		return m_secondary;
	}

private:
	std::shared_ptr<Gun> m_primary = nullptr;
	std::shared_ptr<Gun> m_secondary = nullptr;
};

class brImage;
class brTexture
{
public:
   enum eTextureType{
      TYPE_TEXTURE_2D = 1,
      TYPE_TEXTURE_CUBEMAP = 2
   };

public:
   brTexture(eTextureType type){}
   virtual ~brTexture(){}

   virtual void bind(unsigned int unit) = 0;
   virtual void unbind(unsigned int unit) = 0;
   virtual void update(void) = 0;
};

class brGL3Texture : virtual public brTexture
{
public:
   brGL3Texture(brTexture::eTextureType type):brTexture(type){}
   virtual ~brGL3Texture(){}

   void bind(unsigned int unit){}
   void unbind(unsigned int unit){}
   void update(void){}

protected:
   int m_textureID;
};

class brGL3TextureSampler
{
public:
	brGL3TextureSampler(std::shared_ptr<brTexture> texture)
	:m_texture(texture){}
    virtual ~brGL3TextureSampler(){}

private:
    void init(void){}
    void bindTextureSampler(void){}

	std::shared_ptr<brTexture> m_texture = nullptr;
};

int main() {

	auto delegate1 = brDelegate::create<MachineGun, double, std::string>
	([] (double caliber, const std::string& name) -> std::shared_ptr<MachineGun>
		{ return std::make_shared<MachineGun>(caliber, name); });
        
	auto gun = delegate1->run<MachineGun, double, std::string>(50.0, "BAR");
    // *** type of gun is std::shared_ptr<MachineGun>
    
    // *** this will compile cleanly
    auto test = resolve<Armament, std::shared_ptr<Gun>>( gun );
    // *** equivalent to auto test = resolve<Armament, std::shared_ptr<Gun>>( std::shared_ptr<Gun>(gun) ) ; // rvalue

	auto delegate2 = brDelegate::create<brTexture, brTexture::eTextureType>
		([] (brTexture::eTextureType type) -> std::shared_ptr<brTexture>
			{ return std::make_shared<brGL3Texture>(type); });

	auto texture0 = std::make_shared<brGL3Texture>(brTexture::TYPE_TEXTURE_2D);
    // *** type of texture0 is std::shared_ptr<brGL3Texture>
    
    // *** this will compile cleanly
    auto test0 = resolve<brGL3TextureSampler, std::shared_ptr<brTexture>>( texture0 ) ; // rvalue
    // *** equivalent to auto test = resolve<brGL3TextureSampler, std::shared_ptr<brTexture>>( std::shared_ptr<brTexture>(texture0) ) ; // rvalue
    
	auto texture = delegate2->run<brTexture, brTexture::eTextureType>(brTexture::TYPE_TEXTURE_2D);
    // *** type of texture is std::shared_ptr<brTexture>
    
    // auto test1 = resolve<brGL3TextureSampler, std::shared_ptr<brTexture>>( texture ) ; // lvalue
    // *** error *** no conversion from std::shared_ptr<brTexture>& to std::shared_ptr<brTexture>&&
    
    // *** this will compile cleanly
    auto test2 = resolve<brGL3TextureSampler, std::shared_ptr<brTexture>>( std::shared_ptr<brTexture>(texture) ); // rvalue
    
    // *** this will also compile cleanly; but donot use the object texture after this
    auto test3 = resolve<brGL3TextureSampler, std::shared_ptr<brTexture>>( std::move(texture) ); // rvalue
}
