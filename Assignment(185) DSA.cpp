//Complete Final C++ Code (Single Form)

#include <iostream>
#include <string>
using namespace std;

class ExpenseNode {
	public:
    int expenseId;
    string name;
    float price;
    string date;
    ExpenseNode* next;
};

class UserNode {
	public:
    int userId;
    ExpenseNode* expenseHead;
    UserNode* next;
};

UserNode* userHead = NULL;
int expenseCounter = 1;

UserNode* findUser(int id) {
    UserNode* temp = userHead;
    while (temp && temp->userId != id)
        temp = temp->next;
    return temp;
}

void addUser(int id) {
    if (findUser(id)) {
        cout << "User already exists!\n";
        return;
    }
    UserNode* newUser = new UserNode{id, NULL, NULL};
    if (!userHead) userHead = newUser;
    else {
        UserNode* temp = userHead;
        while (temp->next) temp = temp->next;
        temp->next = newUser;
    }
    cout << "User added!\n";
}

void addExpense(int id, string name, float price, string date) {
    UserNode* user = findUser(id);
    if (!user) {
        cout << "User not found!\n";
        return;
    }
    ExpenseNode* newExp = new ExpenseNode{expenseCounter++, name, price, date, NULL};
    if (!user->expenseHead) user->expenseHead = newExp;
    else {
        ExpenseNode* temp = user->expenseHead;
        while (temp->next) temp = temp->next;
        temp->next = newExp;
    }
    cout << "Expense added!\n";
}

void viewExpenses(int id) {
    UserNode* user = findUser(id);
    if (!user) {
        cout << "User not found!\n";
        return;
    }
    ExpenseNode* temp = user->expenseHead;
    if (!temp) {
        cout << "No expenses found!\n";
        return;
    }

    cout << "ID\tName\t\tPrice\t\tDate\n";
    cout << "-----------------------------------------\n";
    while (temp) {
        cout << temp->expenseId << "\t" << temp->name << "\t\t" << temp->price << "\t\t" << temp->date << "\n";
        temp = temp->next;
    }
}

void editExpense(int userId, int expId, string name, float price, string date) {
    UserNode* user = findUser(userId);
    if (!user) {
        cout << "User not found!\n";
        return;
    }

    ExpenseNode* temp = user->expenseHead;
    while (temp && temp->expenseId != expId)
        temp = temp->next;

    if (!temp) {
        cout << "Expense ID not found!\n";
        return;
    }

    temp->name = name;
    temp->price = price;
    temp->date = date;
    cout << "Expense updated!\n";
}

void deleteExpense(int userId, int expId) {
    UserNode* user = findUser(userId);
    if (!user) {
        cout << "User not found!\n";
        return;
    }

    ExpenseNode* temp = user->expenseHead;
    ExpenseNode* prev = NULL;

    while (temp && temp->expenseId != expId) {
        prev = temp;
        temp = temp->next;
    }

    if (!temp) {
        cout << "Expense ID not found!\n";
        return;
    }

    if (!prev) user->expenseHead = temp->next;
    else prev->next = temp->next;

    delete temp;
    cout << "Expense deleted!\n";
}

void totalExpense(int id) {
    UserNode* user = findUser(id);
    if (!user) {
        cout << "User not found!\n";
        return;
    }
    ExpenseNode* temp = user->expenseHead;
    float total = 0;
    while (temp) {
        total += temp->price;
        temp = temp->next;
    }
    cout << "Total Expense for user " << id << " = Rs " << total << "\n";
}

void report(int userId) {
    UserNode* user = findUser(userId);
    if (!user) {
        cout << "User not found!\n";
        return;
    }

    ExpenseNode* temp = user->expenseHead;
    if (!temp) {
        cout << "No expenses found!\n";
        return;
    }

    ExpenseNode* maxExpense = temp;
    temp = temp->next;

    while (temp) {
        if (temp->price > maxExpense->price)
            maxExpense = temp;
        temp = temp->next;
    }

    cout << "GENERATE A REPORT:\n";
    cout << "ID: " << maxExpense->expenseId << "\n";
    cout << "Name: " << maxExpense->name << "\n";
    cout << "Price: Rs " << maxExpense->price << "\n";
    cout << "Date: " << maxExpense->date << "\n";
}

int main() {
    int choice, userId, expenseId;
    string name, date;
    float price;

    while (true) {
        cout << "\n--- Expense Manager ---\n";
        cout << "1. Add User\n";
        cout << "2. Add Expense\n";
        cout << "3. View Expenses\n";
        cout << "4. Edit Expense\n";
        cout << "5. Delete Expense\n";
        cout << "6. Total Expense\n";
        cout << "7. Exit\n";
        cout << "8. GENERATE A REPORT\n";
        cout << "Choose: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter new user ID: ";
                cin >> userId;
                addUser(userId);
                break;

            case 2:
                cout << "Enter user ID: ";
                cin >> userId;
                cout << "Enter expense name (no spaces): ";
                cin >> name;
                cout << "Enter price: ";
                cin >> price;
                cout << "Enter date (e.g. 2025-05-22): ";
                cin >> date;
                addExpense(userId, name, price, date);
                break;

            case 3:
                cout << "Enter user ID: ";
                cin >> userId;
                viewExpenses(userId);
                break;

            case 4:
                cout << "Enter user ID: ";
                cin >> userId;
                viewExpenses(userId);
                cout << "Enter expense ID to edit: ";
                cin >> expenseId;
                cout << "New name: ";
                cin >> name;
                cout << "New price: ";
                cin >> price;
                cout << "New date: ";
                cin >> date;
                editExpense(userId, expenseId, name, price, date);
                break;

            case 5:
                cout << "Enter user ID: ";
                cin >> userId;
                viewExpenses(userId);
                cout << "Enter expense ID to delete: ";
                cin >> expenseId;
                deleteExpense(userId, expenseId);
                break;

            case 6:
                cout << "Enter user ID: ";
                cin >> userId;
                totalExpense(userId);
                break;

           // case 7:
               // return 0;

            case 7:
                cout << "Enter user ID: ";
                cin >> userId;
                report(userId);
                break;

            default:
                cout << "Invalid choice!\n";
                
				case 8:
                return 0;
        }
    }
}



