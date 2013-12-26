#include <iostream>
#include <string>
#include <vector>

class UpdateListener {
    public:
    virtual void onUpdate(double value) = 0;
};

class PxListener {
    public:
    virtual void onPrice(double px) = 0;
};

/**
 * This will upcast in each function and call the requisite
 * function in DERIVED class
 */
template <typename DERIVED>
class StrategyInterface : public virtual UpdateListener,
                          public virtual PxListener {
    public:
    virtual void onUpdate(double value) {
        static_cast<DERIVED*>(this)->onUpdate(value);
    }
    virtual void onPrice(double px) {
        static_cast<DERIVED*>(this)->onPrice(px);
    }
    // Internal Functions
    void debugUpdate(double value) {
        static_cast<DERIVED*>(this)->debugUpdate(value);
    }
    void debugPrice(double px) {
        static_cast<DERIVED*>(this)->debugPrice(px);
    }
    void debugPriceExtra() {
        static_cast<DERIVED*>(this)->debugPriceExtra();
    }
};

/**
 * This is the base class for all strategies and should have
 * all functions that are present in StrategyInterface defined
 * either empty or valid.
 * 
 * Also, any function called now should always be called on
 * static_cast<DERIVED*>(this)
 */
template <typename DERIVED>
class BasicStrategy : public StrategyInterface<DERIVED> {
    public:
    virtual void onUpdate(double value) {
        std::cout << "BasicStrategy::onUpdate()" << std::endl;
        static_cast<DERIVED*>(this)->debugUpdate(value);
    }
    
    virtual void onPrice(double px) {
        std::cout << "BasicStrategy::onPrice()" << std::endl;
        static_cast<DERIVED*>(this)->debugPrice(px);
    }
    
    void debugUpdate(double value) {
        std::cout << "BasicStrategy::debugUpdate() " << value << std::endl;
    }
    
    void debugPrice(double px) {
        std::cout << "BasicStrategy::debugPrice() " << px << std::endl;
        static_cast<DERIVED*>(this)->debugPriceExtra();
    }
    
    void debugPriceExtra() {
        std::cout << "BasicStrategy::debugPriceExtra() " << std::endl;
    }
};

/**
 * Actual Strategy: If not templatized it's the end of the chain
 * We can choose what functions to define here and what not
 */
class MyStrategy: public BasicStrategy<MyStrategy> {
    public:
    void debugPrice(double px) {
        std::cout << "MyStrategy::debugPrice() " << px << std::endl;
        debugPriceExtra();
    }
};

/**
 * Actual Strategy: If not templatized it's the end of the chain
 * We can choose what functions to define here and what not
 */
class YourStrategy: public BasicStrategy<YourStrategy> {
    public:
    void debugUpdate(double px) {
        std::cout << "YourStrategy::debugUpdate() " << px << std::endl;
    }
};

int main() {
    {
        MyStrategy *s = new MyStrategy();
        PxListener *p = s;
        UpdateListener *u = s;
        s->onUpdate(1.2);
        s->onPrice(1.2);
        u->onUpdate(1.3);
        p->onPrice(1.3);
    }
    {
        YourStrategy *s = new YourStrategy();
        PxListener *p = s;
        UpdateListener *u = s;
        s->onUpdate(1.2);
        s->onPrice(1.2);
        u->onUpdate(1.3);
        p->onPrice(1.3);
    }
}