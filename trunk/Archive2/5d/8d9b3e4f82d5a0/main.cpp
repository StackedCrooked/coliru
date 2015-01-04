namespace Items
{
        class Item;
        class HealingItem;
        class Weapon;
}
//some code cut out for obvious reasons, i'll just show the basic class constructors for the classes
class Items::Item
{
public:
        Item();
//...
};
class Items::HealingItem: public Items::Item
{
//...
public:
        HealingItem();
};
class Items::Weapon: public Items::Item
{
public:
        Weapon();
//...other properties and get/setters
};

 Items::Weapon _equippedWeapon;
 
int main() {}