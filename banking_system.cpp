#include <iostream>
#include <vector>
using namespace std;

class BankAccount
{
protected:
    int accountNumber;
    string accountHolderName;

private:
    double balance; // Encapsulation

public:
    BankAccount(int accNo, string name, double bal)
    {
        accountNumber = accNo;
        accountHolderName = name;
        balance = bal;
    }

    virtual ~BankAccount() {}

    double getBalance()
    {
        return balance;
    }

    void setBalance(double bal)
    {
        balance = bal;
    }

    virtual void deposit(double amount)
    {
        balance += amount;
        cout << "Deposited: Rs." << amount << endl;
    }

    virtual void withdraw(double amount)
    {
        if (amount <= balance)
        {
            balance -= amount;
            cout << "Withdrawn: Rs." << amount << endl;
        }
        else
        {
            cout << "Insufficient Balance!" << endl;
        }
    }

    virtual void calculateInterest() = 0;

    virtual void displayAccountInfo()
    {
        cout << "\nAccount Number : " << accountNumber;
        cout << "\nAccount Holder : " << accountHolderName;
        cout << "\nBalance        : Rs." << balance << endl;
    }
};

class SavingsAccount : public BankAccount
{
private:
    double interestRate;

public:
    SavingsAccount(int accNo, string name, double bal, double rate)
        : BankAccount(accNo, name, bal)
    {
        interestRate = rate;
    }

    void calculateInterest() override
    {
        double interest = getBalance() * interestRate / 100;
        setBalance(getBalance() + interest);

        cout << "Savings Interest Added: Rs."
             << interest << endl;
    }
};

class CheckingAccount : public BankAccount
{
private:
    double overdraftLimit;

public:
    CheckingAccount(int accNo, string name,
                    double bal, double limit)
        : BankAccount(accNo, name, bal)
    {
        overdraftLimit = limit;
    }

    void withdraw(double amount) override
    {
        if (amount <= getBalance() + overdraftLimit)
        {
            setBalance(getBalance() - amount);
            cout << "Withdrawal Successful!" << endl;
        }
        else
        {
            cout << "Overdraft Limit Exceeded!" << endl;
        }
    }

    void calculateInterest() override
    {
        cout << "Checking Account does not provide interest."
             << endl;
    }
};

class FixedDepositAccount : public BankAccount
{
private:
    int term; // months

public:
    FixedDepositAccount(int accNo, string name,
                        double bal, int t)
        : BankAccount(accNo, name, bal)
    {
        term = t;
    }

    void calculateInterest() override
    {
        double rate = 7.0;

        double interest =
            getBalance() * rate * term / (12 * 100.0);

        setBalance(getBalance() + interest);

        cout << "FD Interest Added: Rs."
             << interest << endl;
    }

    void withdraw(double amount) override
    {
        cout << "Withdrawal not allowed before FD maturity!"
             << endl;
    }
};

int main()
{
    vector<BankAccount *> accounts;

    int choice;

    do
    {
        cout << "\n========== BANKING SYSTEM ==========\n";
        cout << "1. Create Savings Account\n";
        cout << "2. Create Checking Account\n";
        cout << "3. Create Fixed Deposit Account\n";
        cout << "4. Display All Accounts\n";
        cout << "5. Deposit Money\n";
        cout << "6. Withdraw Money\n";
        cout << "7. Calculate Interest\n";
        cout << "8. Exit\n";
        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            int accNo;
            string name;
            double bal, rate;

            cout << "Account Number: ";
            cin >> accNo;

            cin.ignore();
            cout << "Holder Name: ";
            getline(cin, name);

            cout << "Initial Balance: ";
            cin >> bal;

            cout << "Interest Rate (%): ";
            cin >> rate;

            accounts.push_back(
                new SavingsAccount(accNo, name, bal, rate));

            cout << "Savings Account Created!\n";
            break;
        }

        case 2:
        {
            int accNo;
            string name;
            double bal, limit;

            cout << "Account Number: ";
            cin >> accNo;

            cin.ignore();
            cout << "Holder Name: ";
            getline(cin, name);

            cout << "Initial Balance: ";
            cin >> bal;

            cout << "Overdraft Limit: ";
            cin >> limit;

            accounts.push_back(
                new CheckingAccount(accNo, name, bal, limit));

            cout << "Checking Account Created!\n";
            break;
        }

        case 3:
        {
            int accNo;
            string name;
            double bal;
            int term;

            cout << "Account Number: ";
            cin >> accNo;

            cin.ignore();
            cout << "Holder Name: ";
            getline(cin, name);

            cout << "Initial Deposit: ";
            cin >> bal;

            cout << "Term (Months): ";
            cin >> term;

            accounts.push_back(
                new FixedDepositAccount(accNo, name, bal, term));

            cout << "Fixed Deposit Account Created!\n";
            break;
        }

        case 4:
        {
            for (auto acc : accounts)
            {
                acc->displayAccountInfo();
                cout << "-------------------------\n";
            }
            break;
        }

        case 5:
        {
            int accNo;
            double amount;

            cout << "Enter Account Number: ";
            cin >> accNo;

            cout << "Enter Amount: ";
            cin >> amount;

            for (auto acc : accounts)
            {
                if (accNo == *((int *)acc))
                {
                    acc->deposit(amount);
                }
            }

            break;
        }

        case 6:
        {
            int index;
            double amount;

            cout << "Enter Account Index (0 onwards): ";
            cin >> index;

            cout << "Amount: ";
            cin >> amount;

            if (index >= 0 && index < accounts.size())
            {
                accounts[index]->withdraw(amount);
            }

            break;
        }

        case 7:
        {
            for (auto acc : accounts)
            {
                acc->calculateInterest(); 
            }
            break;
        }

        case 8:
            cout << "Thank You!\n";
            break;

        default:
            cout << "Invalid Choice!\n";
        }

    } while (choice != 8);

    for (auto acc : accounts)
    {
        delete acc;
    }

    return 0;
}