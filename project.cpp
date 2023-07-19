#include <iostream>
#include <string>
#include <vector>

using namespace std;

#ifdef _WIN32
#include <windows.h> // For Windows
#else
#include <unistd.h> // For Linux and macOS
#endif

#ifdef _WIN32
#include <conio.h> // For Windows
#else
#include <cstdlib> // For Linux and macOS
#endif

// Function to clear the screen
void clearScreen()
{
#ifdef _WIN32
    system("cls"); // For Windows
#else
    system("clear"); // For Linux and macOS
#endif
}

class BankAccount {
private:
    string accountNumber;
    string accountHolder;
    string username;
    string password;
    double balance;
    vector<string> transactionHistory;
    vector<double> transactionAmounts;

public:
    BankAccount(const string& username, const string& password) {
        this->username = username;
        this->password = password;
        balance = 0.0;
        accountNumber = "Not assigned yet";
        accountHolder = "Not assigned yet";
    }

    //GETTER METHODS

    string getUsername() const {
        return username;
    }

    string getAccountNumber() const {
        return accountNumber;
    }

    string getAccountHolder() const {
        return accountHolder;
    }

    bool Password(const string& password) const {
        return this->password == password;
    }

    double getBalance() const {
        return balance;
    }

    //Setter method
    void setAccountInfo(const string& accountNumber, const string& accountHolder, double initialBalance) {
        this->accountNumber = accountNumber;
        this->accountHolder = accountHolder;
        balance = initialBalance;
    }

    
    void deposit(double amount) {    //Balance amount gets updated after adding money
        balance += amount;
        cout << "Deposit successful.\n";
        transactionHistory.push_back("Deposit");
        transactionAmounts.push_back(amount);
    }

    bool withdraw(double amount) {      //Balance amount gets updated after withrawing money
        if (amount <= balance) {
            balance -= amount;
            cout << "Withdrawal successful.\n";
            transactionHistory.push_back("Withdrawal");
            transactionAmounts.push_back(amount);
            return true;
        } else {
            cout << "Insufficient balance.\n";
            return false;
        }
    }

    void printTransactionHistory() const {                 // Print Transaction history
        cout << "=== Transaction History ===" << endl;
        if (transactionHistory.empty()) {
            cout << "No transactions found." << endl;
        } else {
            for (size_t i = 0; i < transactionHistory.size(); i++) {
                cout << "Transaction: " << transactionHistory[i] << endl;
                cout << "Amount: $" << transactionAmounts[i] << endl;
                cout << "-----------------------------" << endl;
            }
        }
    }

    void displayAccountInfo() const {               //Display account details of user logged in
        cout << "Account Number: " << accountNumber << endl;
        cout << "Account Holder: " << accountHolder << endl;
        cout << "Current Balance: " << balance << endl;
    }


    //Update account details of user logged in
    void updateAccountInfo(const string& newAccountNumber, const string& newAccountHolder) {  
        if (accountNumber == "Not assigned yet" && accountHolder == "Not assigned yet") {
            accountNumber = newAccountNumber;
            accountHolder = newAccountHolder;
            cout << "Account information set.\n";
        } else {
            accountNumber = newAccountNumber;
            accountHolder = newAccountHolder;
            cout << "Account information updated.\n";
        }
    }
};


bool validateUsername(const vector<BankAccount>& accounts, const string& username) {
    for (const auto& account : accounts) {
        if (account.getUsername() == username) {
            return false;  // Username already exists
        }
    }
    return true;  // Username is valid
}

bool validatePassword(const string& password) {
    try {
        if (password.length() < 8) {
            throw length_error("Password should have at least 8 characters.");
        }

        bool hasUppercase = false;
        bool hasLowercase = false;
        bool hasDigit = false;

        for (char ch : password) {
            if (isupper(ch)) {
                hasUppercase = true;
            } else if (islower(ch)) {
                hasLowercase = true;
            } else if (isdigit(ch)) {
                hasDigit = true;
            }
        }

        if (!hasUppercase || !hasLowercase || !hasDigit) {
            throw invalid_argument("Password should contain at least one uppercase letter, one lowercase letter, and one digit.");
        }

        return true;  // Password is valid
    } catch (const exception& e) {
        cout << "Invalid password: " << e.what() << endl;
        return false;  // Password is invalid
    }
}

bool signup(vector<BankAccount>& accounts, const string& username, const string& password) {
    if (!validateUsername(accounts, username)) {
        cout << "Username already exists. Please choose a different username.\n";
        return false;
    }

    if (!validatePassword(password)) {
        //ValidatePassword function already prints the error message.
        return false;
    }

    BankAccount newAccount(username, password);
    accounts.push_back(newAccount);
    cout << "Signup successful. Please login with your new account.\n";
    return true;
}

void displayAllAccounts(const vector<BankAccount>& accounts) {  //displays details of all accounts signed up
    if (accounts.empty()) {
        cout << "No accounts found.\n";
    } else {
        cout << "=== All Accounts ===\n";
        for (const auto& account : accounts) {
            cout << "Username: " << account.getUsername() << endl;
            cout << "Account Number: " << account.getAccountNumber() << endl;
            cout << "Account Holder: " << account.getAccountHolder() << endl;
            cout << "Balance: " << account.getBalance() << endl;
            cout << "-------------------------\n";
        }
    }
}

//Delete account based on account number and password
bool deleteAccount(vector<BankAccount>& accounts, const string& accountNumber, const string& password) {
    for (auto it = accounts.begin(); it != accounts.end(); ++it) {
        if (it->getAccountNumber() == accountNumber && it->Password(password)) {
            accounts.erase(it);
            cout << "Account deleted successfully.\n";
            return true;
        }
    }
    cout << "Account not found or password is incorrect.\n";
    return false;
}

int main() {
    vector<BankAccount> accounts;
    string username, password;
    int choice;

    while (true) {  //Start Menu
        cout << "=== Bank Application ===\n";
        cout << "1. Signup\n";
        cout << "2. Login\n";
        cout << "3. Display All Accounts\n";
        cout << "4. Delete Account\n";
        cout << "5. Exit\n";
        cout << "Enter your choice (1-5): ";
        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "=== Signup ===\n";
                cout << "Username: ";
                cin >> username;
                cout << "Password: ";
                cin >> password;
                signup(accounts, username, password);

            #ifdef _WIN32
                Sleep(3000); // For Windows
            #endif

                clearScreen();

                break;
            }
            case 2: {
                cout << "=== Login ===\n";
                cout << "Username: ";
                cin >> username;
                cout << "Password: ";
                cin >> password;

                bool found = false;
                for (auto& account : accounts) {
                    if (account.getUsername() == username) {
                        if (account.Password(password)) {
                            found = true;
                            cout << "Login successful. Welcome, " << username << "!\n";

                        #ifdef _WIN32
                            Sleep(3000); // For Windows
                        #endif

                            clearScreen();

                            if (account.getBalance() == 0.0) {
                                string accountNumber, accountHolder;
                                double initialBalance;
                                cout << "Hello, " << username << "---------\n";
                                cout << "Enter Account Number: ";
                                cin >> accountNumber;
                                cout << "Enter Account Holder: ";
                                cin.ignore();
                                getline(cin, accountHolder);
                                cout << "Enter Initial Balance: ";
                                cin >> initialBalance;

                                account.setAccountInfo(accountNumber, accountHolder, initialBalance);

                            #ifdef _WIN32
                                Sleep(3000); // For Windows
                            #endif

                                clearScreen();
                            }

                            // Display account operations menu
                            int accountChoice;
                            do {
                                cout << "\n=== Account Menu ===\n";
                                cout << "1. Deposit\n";
                                cout << "2. Withdraw\n";
                                cout << "3. Balance Inquiry\n";
                                cout << "4. Update Account Info\n";
                                cout << "5. View Transaction History\n";
                                cout << "6. Logout\n";
                                cout << "Enter your choice (1-6): ";
                                cin >> accountChoice;

                                switch (accountChoice) {
                                    case 1: {
                                        double amount;
                                        cout << "Enter the amount to deposit: ";
                                        cin >> amount;
                                        account.deposit(amount);

                                    #ifdef _WIN32
                                        Sleep(3000); // For Windows
                                    #endif

                                        clearScreen();
                                        break;
                                    }
                                    case 2: {
                                        double amount;
                                        cout << "Enter the amount to withdraw: ";
                                        cin >> amount;
                                        account.withdraw(amount);

                                    #ifdef _WIN32
                                        Sleep(3000); // For Windows
                                    #endif

                                        clearScreen();
                                        break;
                                    }
                                    case 3:
                                        account.displayAccountInfo();

                                    #ifdef _WIN32
                                        Sleep(3000); // For Windows
                                    #endif

                                        clearScreen();
                                        break;

                                    case 4: {
                                        string newAccountNumber, newAccountHolder;
                                        cout << "Enter new Account Number: ";
                                        cin >> newAccountNumber;
                                        cout << "Enter new Account Holder: ";
                                        cin.ignore();
                                        getline(cin, newAccountHolder);
                                        account.updateAccountInfo(newAccountNumber, newAccountHolder);

                                    #ifdef _WIN32
                                        Sleep(3000); // For Windows
                                    #endif

                                        clearScreen();
                                        break;
                                    }

                                    case 5: {
                                        account.printTransactionHistory();

                                    #ifdef _WIN32
                                        Sleep(3000); // For Windows
                                    #endif

                                        clearScreen();
                                        break;
                                    }
                                    case 6:
                                        cout << "Logging out...\n";

                                    #ifdef _WIN32
                                        Sleep(3000); // For Windows
                                    #endif

                                        clearScreen();
                                        break;
                                    default:
                                        cout << "Invalid choice. Please try again.\n";

                                    #ifdef _WIN32
                                        Sleep(3000); // For Windows
                                    #endif

                                        clearScreen();
                                }
                            } while (accountChoice != 6);

                            break;
                        } else {
                            found = true;
                            cout << "Password entered is incorrect.\n";

                        #ifdef _WIN32
                            Sleep(3000); // For Windows
                        #endif

                            clearScreen();
                        }
                    }
                }

                if (!found) {
                    cout << "Account not found. Please signup or enter correct login credentials.\n";

                #ifdef _WIN32
                    Sleep(3000); // For Windows
                #endif

                    clearScreen();
                }
                break;
            }
            case 3:
                displayAllAccounts(accounts);

            #ifdef _WIN32
                Sleep(3000); // For Windows
            #endif

                clearScreen();
                break;

            case 4: {
                cout << "=== Delete Account ===\n";
                if (accounts.empty()) {
                    cout << "No accounts yet.\n";

                #ifdef _WIN32
                    Sleep(3000); // For Windows
                #endif

                    clearScreen();
                } else {
                    string accountNumber;
                    cout << "Account Number: ";
                    cin >> accountNumber;
                    cout << "Password: ";
                    cin >> password;

                    deleteAccount(accounts, accountNumber, password);

                #ifdef _WIN32
                    Sleep(3000); // For Windows
                #endif

                    clearScreen();
                }

                break;
            }
            case 5:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";

            #ifdef _WIN32
                Sleep(3000); // For Windows
            #endif

                clearScreen();
                break;
        }
    }

    return 0;
}
