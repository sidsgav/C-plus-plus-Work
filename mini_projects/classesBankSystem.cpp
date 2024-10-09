#include <iostream>
#include <string>

class BankAccount {
private:
    std::string accountNumber;
    double balance;
    std::string accountHolderName;

public:
    // Constructor
    BankAccount(const std::string& accNumber, double initialBalance, const std::string& accHolderName)
        : accountNumber(accNumber), balance(initialBalance), accountHolderName(accHolderName) {}

    // Deposit method
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            std::cout << "Deposited $" << amount << " into account " << accountNumber << std::endl;
        } else {
            std::cout << "Invalid deposit amount" << std::endl;
        }
    }

    // Withdraw method
    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            std::cout << "Withdrawn $" << amount << " from account " << accountNumber << std::endl;
        } else {
            std::cout << "Insufficient funds or invalid withdrawal amount" << std::endl;
        }
    }

    // Display account information
    void displayAccountInfo() const {
        std::cout << "Account Number: " << accountNumber << std::endl;
        std::cout << "Account Holder Name: " << accountHolderName << std::endl;
        std::cout << "Balance: $" << balance << std::endl;
    }
};

int main() {
    // Create instances of the BankAccount class
    BankAccount account1("123456789", 1000.0, "Gavin");
    BankAccount account2("987654321", 500.0, "Sam");

    // Perform transactions
    account1.deposit(200.0);
    account2.withdraw(100.0);

    // Display account information
    std::cout << "Account 1 Information:" << std::endl;
    account1.displayAccountInfo();

    std::cout << std::endl;

    std::cout << "Account 2 Information:" << std::endl;
    account2.displayAccountInfo();

    return 0;
}