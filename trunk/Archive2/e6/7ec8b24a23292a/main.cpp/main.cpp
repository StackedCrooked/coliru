    #include <iostream>
    #include <string>
    
    // Properties for all objects of Base type
    class BaseProperties {
    public:
      BaseProperties( std::string baseProperty ):
        baseProperty_( baseProperty ) { }
        
      virtual ~BaseProperties(  ) {  }
      std::string getBaseProperty(  ) const { return baseProperty_; }
        
    protected:
      std::string baseProperty_;
    };
    
    // Properties specific to objects of Derived type
    class DerivedProperties: public BaseProperties {
    public:
      DerivedProperties( std::string baseProperty, std::string derivedProperty ):
        BaseProperties( baseProperty ),
        derivedProperty_( derivedProperty ) {  }
      
      std::string getDerivedProperty(  ) { return derivedProperty_; }
        
    private:
      std::string derivedProperty_;
    };
    
    class Base {
    public:
      Base( BaseProperties& properties ):
        properties_( properties ) {  }
        
      virtual ~Base(  ) {  }
      
    protected:
      BaseProperties& properties_;
    };
    
    class Derived : public Base {
    public:
      Derived( DerivedProperties& properties ):
        Base( properties ) {  }
      
      friend std::ostream & operator << ( std::ostream& out, const Derived& derived );
    };
    
    std::ostream & operator << ( std::ostream& out, const Derived& derived ) {  
      return out << derived.properties_.getBaseProperty(  ) << ", "
                 << dynamic_cast< DerivedProperties& >( derived.properties_ ).getDerivedProperty(  );
    }
    
    int main(  ) {
      DerivedProperties properties( "BaseProperty", "DerivedProperty" );
      Derived derived( properties );
      
      std::cout << derived << std::endl;
      return 0;
    }