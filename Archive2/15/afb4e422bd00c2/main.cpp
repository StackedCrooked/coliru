#include <memory>
#include <vector>

struct String{ };
struct Vector2f { };
struct sf { struct Text { }; };

class Monkey
{
public:
    virtual ~Monkey(){}
    virtual void clearMonkeys() = 0;
    virtual std::shared_ptr<std::vector<sf::Text>> getMonkeyListPtr() = 0;
    virtual void addMonkey(String message,Vector2f position,float depthValue) = 0;
};

class NullMonkey : public Monkey
{
public:
    NullMonkey () {/*Do Nothing*/}
    virtual ~NullMonkey () {/*Do Nothing*/}
    virtual void clearMonkeys(){/*Do Nothing*/};
    virtual std::shared_ptr<std::vector<sf::Text>> getMonkeyListPtr()
    {
        //Do Nothing but...
        //Return NULL shared pointer
        std::shared_ptr<std::vector<sf::Text>> nullSharedPointer;
        return nullSharedPointer;
        //Of course I am ASSUMING I will check for NULL pointer...
    }
    virtual void addMonkey(String message,Vector2f position,float depthValue){/*Do Nothing*/};
};

class ServLoc
{
public:

    ServLoc();

    static void initialize()
    {
        theMonkey = &theNullMonkey; //Error here
    }

    //...

    static Monkey* theMonkey;
    static NullMonkey theNullMonkey;
};

NullMonkey ServLoc::theNullMonkey;
Monkey* ServLoc::theMonkey;

int main() {
    ServLoc::initialize();
}