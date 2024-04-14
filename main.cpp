#include <iostream>

#include <fstream>

#include <sstream>

#include <map>

#include <string>



using namespace std;



// Define a class called ATM to handle banking operations

class ATM {

private:

map<string, float> accounts; // A map to store account numbers (as strings) and their corresponding balances (as floating-point numbers)



public:

// Function to load account information from a file

void loadAccountsFromFile(const string& filename) {

ifstream file(filename);

if (file.is_open()) {

string line;

while (getline(file, line)) {

stringstream ss(line);

string accountNumber;

float balance; // Variable to store the balance

ss >> accountNumber >> balance; // Extract the account number and balance from the line

accounts[accountNumber] = balance; // Store the account number and balance in the map

}

file.close(); // Close the file after reading

}

}



// Function to save account information to a file

void saveAccountsToFile(const string& filename) {

ofstream file(filename);

if (file.is_open()) { // If the file is successfully opened

for (const auto& pair : accounts) { // Iterate over each pair in the map

file << pair.first << " " << pair.second << endl; // Write the account number and balance to the file

}

file.close();

}

}



// Function to create an account with a given account number and starting balance

void createAccount(const string& accountNumber, float balance) {

accounts[accountNumber] = balance; // Add the account number and balance to the map

cout << "Account created!" << endl;

saveAccountsToFile("accounts.txt"); // Save the updated account information to the file

}



// Function to check if an account exists with a given account number and log in

bool login(const string& accountNumber) {

if (accounts.find(accountNumber) != accounts.end()) { // If the account number exists in the map

cout << "Welcome to your account!" << endl;

return true; // Return true to indicate successful login

} else { // If the account number does not exist in the map

cout << "Account does not exist!" << endl; // Print an error message

return false; // Return false to indicate unsuccessful login

}

}



// Function to deposit money into an existing account with a given account number and amount

void deposit(const string& accountNumber, float amount) {

accounts[accountNumber] += amount; // Increase the balance for the specified account by the specified amount

cout << "Money deposited!" << endl;

cout << "New balance: " << accounts[accountNumber] << endl;

saveAccountsToFile("accounts.txt"); // Save the updated account information to the file

}



// Function to withdraw money from an existing account with a given account number and amount

void withdraw(const string& accountNumber, float amount) {

if (accounts[accountNumber] >= amount) { // If there is enough balance in the account to cover the requested amount

accounts[accountNumber] -= amount; // Decrease the balance for the specified account by the specified amount

cout << "Money withdrawn!" << endl;

cout << "New balance: " << accounts[accountNumber] << endl;

saveAccountsToFile("accounts.txt"); // Save the updated account information to the file

} else { // If there is not enough balance in the account

cout << "Insufficient balance!" << endl;

}

}

};





int main() {

ATM atm;



int choice;

string accountNumber;

float balance, amount;



// Main menu for the ATM

do {

cout << "\nSelect option:" << endl;

cout << "1. Create account" << endl;

cout << "2. Login" << endl;

cout << "3. Deposit money" << endl;

cout << "4. Withdraw money" << endl;

cout << "5. Exit" << endl;

cout << "Enter your choice: ";

cin >> choice;



switch (choice) { // Depending on the user's choice, perform a certain action

case 1:

cout << "Enter account number: ";

cin >> accountNumber;

cout << "Enter balance: ";

cin >> balance;

atm.createAccount(accountNumber, balance);

break;

case 2:

cout << "Enter account number: ";

cin >> accountNumber;

if (atm.login(accountNumber)) { // If the login is successful

do { // Show submenu for transactions

cout << "\nSelect option:" << endl;

cout << "1. Deposit money" << endl;

cout << "2. Withdraw money" << endl;

cout << "3. Logout" << endl;

cout << "Enter your choice: ";

cin >> choice;

switch (choice) {

case 1:

cout << "Enter amount to deposit: ";

cin >> amount;

atm.deposit(accountNumber, amount);

break;

case 2:

cout << "Enter amount to withdraw: ";

cin >> amount;

atm.withdraw(accountNumber, amount);

break;

case 3:

cout << "Logging out..." << endl;

break;

default:

cout << "Invalid choice! Please try again." << endl;

}

} while (choice != 3); // Repeat submenu until user logs out

}

break;

case 3: // If the user chooses to deposit money before logging in

cout << "This option is only available after logging in!" << endl;

break;

case 4: // If the user chooses to withdraw money before logging in

cout << "This option is only available after logging in!" << endl;

break;

case 5: // If the user chooses to exit the program

cout << "Exiting..." << endl;

break;

default: // If the user makes an invalid choice in the main menu

cout << "Invalid choice! Please try again." << endl;

}

} while (choice != 5); // Repeat the loop until the user chooses to exit



return 0;

}

