#include <iostream>
#include <vector>
#include "bank_customer.h"
#include "buyer.h"

enum PrimaryPrompt{LOGIN, REGISTER, EXIT};
enum RegisterPrompt { CREATE_BUYER, CREATE_SELLER, BACK };

using namespace std;

int main() {
    vector<BankCustomer> bankCustomers;
    vector<Buyer> buyers;

    int buyerCounter = 1;
    int bankCustomerCounter = 1;

    PrimaryPrompt prompt = LOGIN;
    while (prompt != EXIT) {
        cout << "Select an option: " << endl;
        cout << "1. Login" << endl;
        cout << "2. Register" << endl;
        cout << "3. Exit" << endl;

        int choice;
        cin >> choice;
        prompt = static_cast<PrimaryPrompt>(choice - 1);

        switch (prompt) {
            case LOGIN: {
                cout << "Login selected." << endl;
                if (buyers.empty()) {
                    cout << "No buyers registered yet. Please register first." << endl;
                    break;
                }

                cout << "Enter Buyer ID: ";
                int loginId;
                cin >> loginId;

                Buyer* loggedInBuyer = nullptr;
                for (auto &b : buyers) {
                    if (b.getId() == loginId) {
                        loggedInBuyer = &b;
                        break;
                    }
                }

                if (!loggedInBuyer) {
                    cout << "Invalid Buyer ID." << endl;
                    break;
                }

                bool inSession = true;
                while (inSession) {
                    cout << "Buyer Menu" << endl;
                    cout << "1. Check Account Status" << endl;
                    cout << "2. Upgrade Account to Seller (NOT IMPLEMENTED - TODO)" << endl;
                    cout << "3. Banking Functions" << endl;
                    cout << "4. Logout" << endl;

                    int menuChoice;
                    cin >> menuChoice;

                    switch (menuChoice) {
                        case 1:
                            cout << " Account Info " << endl;
                            loggedInBuyer->getAccount().printInfo();
                            break;

                        case 2:
                            cout << "Upgrade to Seller selected" << endl;
                            cout << "TODO: Implement seller creation, link to Buyer + BankAccount. " << endl;
                            break;

                        case 3: {
                            bool inBank = true;
                            while (inBank) {
                                cout << "Banking Menu" << endl;
                                cout << "1. Check Balance" << endl;
                                cout << "2. Deposit" << endl;
                                cout << "3. Withdraw" << endl;
                                cout << "4. Back" << endl;

                                int bankChoice;
                                cin >> bankChoice;

                                switch (bankChoice) {
                                    case 1:
                                        cout << "Balance: $" 
                                            << loggedInBuyer->getAccount().getBalance() << endl;
                                        break;
                                    case 2: {
                                        cout << "Enter deposit amount: ";
                                        double amt; cin >> amt;
                                        if (amt <= 0) {
                                            cout << "Invalid amount." << endl;
                                        } else {
                                            loggedInBuyer->getAccount().addBalance(amt);
                                            cout << "Deposited $" << amt << ". New balance: $" << loggedInBuyer->getAccount().getBalance() << endl;
                                        }
                                        break;
                                    }
                                    case 3: {
                                        cout << "Enter withdraw amount: ";
                                        double amt; cin >> amt;
                                        if (amt <= 0) {
                                            cout << "Invalid amount." << endl;
                                        } else {
                                            bool ok = loggedInBuyer->getAccount().withdrawBalance(amt);
                                            if (ok) {
                                                cout << "Withdrawn $" << amt << ". New balance: $" << loggedInBuyer->getAccount().getBalance() << endl;
                                            }
                                        }
                                        break;
                                    }
                                    case 4:
                                        inBank = false;
                                        break;
                                    default:
                                        cout << "Invalid option." << endl;
                                        break;
                                }
                            }
                            break;
                        }

                        case 4:
                            cout << "Logging out..." << endl;
                            inSession = false;
                            break;

                        default:
                            cout << "Invalid option." << endl;
                            break;
                    }
                } 
                break;
            }

            case REGISTER: {
                RegisterPrompt regPrompt = CREATE_BUYER;
                while (regPrompt != BACK) {
                    cout << "Register selected" << endl;
                    cout << "1. Create Buyer Account" << endl;
                    cout << "2. Create Seller Account" << endl;
                    cout << "3. Back" << endl;

                    int regChoice;
                    cin >> regChoice;
                    regPrompt = static_cast<RegisterPrompt>(regChoice - 1);

                    switch (regPrompt) {
                        case CREATE_BUYER: {
                            string name;
                            double initDeposit;
                            cout << "Enter Buyer Name: ";
                            cin >> ws;
                            getline(cin, name);
                            cout << "Enter Initial Deposit: ";
                            cin >> initDeposit;
                            if (initDeposit < 0) initDeposit = 0.0;

                            BankCustomer bc(bankCustomerCounter++, name, initDeposit);
                            bankCustomers.push_back(bc);

                            buyers.emplace_back(buyerCounter++, name, bankCustomers.back());
                            cout << "Buyer created. Buyer ID: " << buyers.back().getId() << ", Bank ID: " << bankCustomers.back().getId() << endl;
                            break;
                        }

                        case CREATE_SELLER:
                            cout << "Create Seller Account" << endl;
                            cout << "Currently: please first create a Buyer account, then ask instructor for upgrade steps." << endl;
                            break;

                        case BACK:
                            cout << "Returning to main menu." << endl;
                            break;

                        default:
                            cout << "Invalid option." << endl;
                            break;
                    }
                }
                break;
            }

            case EXIT: {
                cout << "Exiting program..." << endl;
                break;
            }

            default:
                cout << "Invalid option." << endl;
                break;
        }
        cout << endl;
    }

    return 0;
}