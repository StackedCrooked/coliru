#include <iostream>
#include <memory>

enum class ChainType {
    None,
    And,
    Or
};

struct Bool : std::enable_shared_from_this<Bool> {
    bool active = false;
    std::shared_ptr<Bool> left;
    std::shared_ptr<Bool> right;
    ChainType type = ChainType::None;

    Bool() = default;
    Bool(bool b): active(b) {}

    bool is_expression() const noexcept {
        return left != nullptr && right != nullptr;
    }

    void evaluate(std::shared_ptr<Bool> node) {
        if(node == nullptr)
            return;
        evaluate(node->left);
        evaluate(node->right);

        std::cout << (node->active ? "true\n" : "false\n");

        if(node->is_expression()) {
            switch(node->type) {
            case ChainType::And:
                node->active = node->left->active && node->right->active;
                break;
            case ChainType::Or:
                node->active = node->left->active || node->right->active;
                break;
            case ChainType::None:
                break;
            }

            active = node->active;
        }
    }

    explicit operator bool() noexcept {
        if(is_expression())
            evaluate(std::shared_ptr<Bool>(this));
        return active;
    }
};

Bool operator&&(const Bool& lhs, const Bool& rhs) {
    Bool result;
    result.left = std::make_shared<Bool>(lhs);
    result.right = std::make_shared<Bool>(rhs);
    result.type = ChainType::And;
    return result;
}

Bool operator||(const Bool& lhs, const Bool& rhs) {
    Bool result;
    result.left = std::make_shared<Bool>(lhs);
    result.right = std::make_shared<Bool>(rhs);
    result.type = ChainType::Or;
    return result;
}

int main() {
    Bool a(true);
    Bool b(false);
    Bool c(true);
    auto lol = (a && b) || c;
    if(lol) {
        std::cout << "...";
    }
}