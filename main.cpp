#include <iostream>
#include <string>
#include <vector>
#include <limits>

using namespace std;

struct Appliance {
    string name;
    double power;
    double hours;
};

vector<Appliance> appliances;

void clearBadInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

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

void registerAppliance() {
    Appliance appliance;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter appliance name: ";
    getline(cin, appliance.name);

    cout << "Enter power rating (W): ";
    cin >> appliance.power;

    if (cin.fail()) {
        clearBadInput();
        cout << "Invalid power input.\n";
        return;
    }

    cout << "Enter usage hours per day: ";
    cin >> appliance.hours;

    if (cin.fail()) {
        clearBadInput();
        cout << "Invalid hours input.\n";
        return;
    }

    appliances.push_back(appliance);

    cout << "Appliance registered successfully.\n";
}

int main() {
    int choice;

    do {
        showMenu();
        cin >> choice;

        if (cin.fail()) {
            clearBadInput();
            choice = -1;
        }

        if (choice == 1) {
            registerAppliance();
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
