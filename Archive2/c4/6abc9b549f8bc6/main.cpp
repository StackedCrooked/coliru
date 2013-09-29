#include <iostream>
#include <memory>

struct Action {
    using pointer = std::unique_ptr<Action>;
    struct Chain {
        pointer lhs;
        pointer rhs;
        Chain(pointer one, pointer two): lhs(std::move(one)), rhs(std::move(two)) {}
        virtual bool isActive() const noexcept = 0;
    };
    
    struct OrChain : Chain {
        OrChain(pointer lhs, pointer rhs): Chain(std::move(lhs), std::move(rhs)) {}
        virtual bool isActive() const noexcept {
            return lhs->active || rhs->active;
        }
    };
    
    struct AndChain : Chain {
        AndChain(pointer lhs, pointer rhs): Chain(std::move(lhs), std::move(rhs)) {}
        virtual bool isActive() const noexcept {
            return lhs->active && rhs->active;
        }
    };
    
    bool active = false;
    
    std::shared_ptr<Chain> chain_type;
    
    Action() = default;
    
    Action(std::shared_ptr<Chain> chain): chain_type(std::move(chain)) {}
    
    friend Action operator&(const Action& lhs, const Action& rhs) {
        return Action(std::make_shared<AndChain>(std::unique_ptr<Action>(new Action(lhs)), std::unique_ptr<Action>(new Action(rhs))));
    }
};


int main() {
}