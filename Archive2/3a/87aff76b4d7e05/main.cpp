#include <memory>

class BankAccount {
 private:
  class SavingsAccount;
  class ChequingAccount;
  BankAccount() = default;  // prevent third-party subclassing
 public:
  virtual ~BankAccount() {}
  virtual int getBalance() = 0;
  static std::unique_ptr<BankAccount> makeSavingsAccount();
  static std::unique_ptr<BankAccount> makeChequingAccount();  
};

class BankAccount::SavingsAccount final : public BankAccount {
 public:
  int getBalance() override { return 0; }
};

class BankAccount::ChequingAccount final : public BankAccount {
 public:
  int getBalance() override { return 1; }
};

std::unique_ptr<BankAccount>
BankAccount::makeSavingsAccount() {
  return std::make_unique<SavingsAccount>();
}

std::unique_ptr<BankAccount>
BankAccount::makeChequingAccount() {
  return std::make_unique<ChequingAccount>();
}

class BadAccount : public BankAccount {
 public:
  int getBalance() override { return 1000000; }
};

//class AnotherBadAccount : public SavingsAccount {  // Not allowed
// public:
//  int getBalance() override { return 1000000; }
//};

int main() {
//   BadAccount badaccount;  // Not allowed
   auto savings = BankAccount::makeSavingsAccount();
   auto chequing = BankAccount::makeChequingAccount();
}
