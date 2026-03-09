#include <iostream>

using namespace std;

void showMenu() {
    cout << "\n==============================\n";
    cout << " Electrical Load Monitoring\n";
    cout << "==============================\n";
    cout << "1. Register appliance\n";
    cout << "2. View appliances\n";
    cout << "3. Search appliance\n";
    cout << "4. Energy summary\n";
    cout << "5. Calculate electricity bill\n";
    cout << "0. Exit\n";
    cout << "Choose: ";
}

int main() {
    int choice;

    do {
        showMenu();
        cin >> choice;

        if (choice == 1) {
            cout << "Register appliance selected.\n";
        } else if (choice == 2) {
            cout << "View appliances selected.\n";
        } else if (choice == 3) {
            cout << "Search appliance selected.\n";
        } else if (choice == 4) {
            cout << "Energy summary selected.\n";
        } else if (choice == 5) {
            cout << "Calculate bill selected.\n";
        } else if (choice == 0) {
            cout << "Goodbye\n";
        } else {
            cout << "Invalid choice\n";
        }

    } while (choice != 0);

    return 0;
}