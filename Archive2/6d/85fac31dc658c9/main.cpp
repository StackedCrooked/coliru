#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <memory>

struct Object
{
    Object( std::string name, int worth, double weight ) : name(name), worth(worth), weight(weight) {}
    virtual ~Object() = default ;

    using attribute_map = std::map< std::string, std::string > ; // name-value pairs

    virtual attribute_map attributes() const
    { return { { "name", name }, { "worth", std::to_string(worth) }, { "weight", std::to_string(weight) } }; }

    std::string name;
    int worth;
    double weight;
}; //Example base class all the derived classes from this class will need 
   // every member from Object (string name, int worth, etc

struct Weapon : public Object
{
    Weapon( std::string name, int worth, double weight, int damage ) : Object(name,worth,weight), damage(damage) {}
    int damage;

    virtual attribute_map attributes() const override
    { 
        auto result =  Object::attributes() ;
        result.emplace( "damage", std::to_string(damage) ) ; 
        return result ;
    }
}; //Weapon class. has int damage which none other class needs BUT Weapon.

struct Armor : public Object
{
    Armor( std::string name, int worth, double weight, short defense ) : Object(name,worth,weight), defense(defense) {}
    short defense;
    
    virtual attribute_map attributes() const override
    { 
        auto result =  Object::attributes() ;
        result.emplace( "defense", std::to_string(defense) ) ; 
        return result ;
    }
}; //again, has a member called defense no other class needs.

int main()
{
    std::vector< std::unique_ptr<Object> > objects ;
    objects.emplace_back( new Object( "one", 2, 3.3 ) ) ;
    objects.emplace_back( new Weapon( "two", 4, 5.5, 6 ) ) ;
    objects.emplace_back( new Armor( "three", 7, 8.8, 9 ) ) ;
    objects.emplace_back( new Weapon( "four", 10, 11.1, 12 ) ) ;
    objects.emplace_back( new Armor( "five", 13, 14.4, 15) ) ;
    
    int total_worth = 0, total_damage = 0, total_defense = 0 ;
    double  total_weight = 0.0 ;
    
    for( const auto& ptr : objects ) 
    {
         auto attrib = ptr->attributes() ;
         
         std::cout << attrib["name"] << ' ' ;
         
         total_worth += std::stoi(attrib["worth"]) ;
         total_weight += std::stod(attrib["weight"]) ;
         
         if( !attrib["damage"].empty() ) total_damage += std::stoi(attrib["damage"]) ;
         if( !attrib["defense"].empty() )total_defense += std::stoi(attrib["defense"]) ;
    }
    
    std::cout << "\ntotal_worth: " << total_worth << "\ntotal_weight: " << total_weight  
              << "\ntotal_damage: " << total_damage << "\ntotal_defense: "  << total_defense << '\n' ; 
              
    // apply stats to player          
}
