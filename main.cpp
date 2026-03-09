
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>

using namespace std;

const string APPLIANCE_FILE = "appliances.txt";

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

string makeLowercase(string text) {
    for (int i = 0; i < text.size(); i++) {
        if (text[i] >= 'A' && text[i] <= 'Z') {
            text[i] = text[i] + 32;
        }
    }
    return text;
}

double energyPerDay(const Appliance& appliance) {
    return (appliance.power * appliance.hours) / 1000.0;
}

double totalEnergyUsed() {
    double total = 0;

    for (int i = 0; i < appliances.size(); i++) {
        total = total + energyPerDay(appliances[i]);
    }

    return total;
}

void saveToFile(const Appliance& appliance) {
    ofstream file(APPLIANCE_FILE, ios::app);

    if (file.is_open()) {
        file << appliance.name << "," << appliance.power << "," << appliance.hours << endl;
        file.close();
    }
}

void loadFromFile() {
    ifstream file(APPLIANCE_FILE);

    if (!file.is_open()) {
        return;
    }

    while (true) {
        Appliance appliance;
        string powerText;
        string hoursText;

        if (!getline(file, appliance.name, ',')) {
            break;
        }

        if (!getline(file, powerText, ',')) {
            break;
        }

        if (!getline(file, hoursText)) {
            break;
        }

        appliance.power = stod(powerText);
        appliance.hours = stod(hoursText);

        appliances.push_back(appliance);
    }

    file.close();
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
    saveToFile(appliance);

    cout << "Appliance registered successfully.\n";
}

void viewAppliances() {
    if (appliances.empty()) {
        cout << "No appliances registered.\n";
        return;
    }

    cout << "\nAppliances List\n";

    for (int i = 0; i < appliances.size(); i++) {
        cout << i + 1 << ". "
             << appliances[i].name
             << " | Power: " << appliances[i].power << "W"
             << " | Hours: " << appliances[i].hours
             << endl;
    }
}

void searchAppliance() {
    if (appliances.empty()) {
        cout << "No appliances available.\n";
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string searchName;
    cout << "Enter appliance name: ";
    getline(cin, searchName);

    searchName = makeLowercase(searchName);

    bool found = false;

    for (int i = 0; i < appliances.size(); i++) {
        string currentName = makeLowercase(appliances[i].name);

        if (currentName.find(searchName) != string::npos) {
            cout << appliances[i].name
                 << " | " << appliances[i].power << "W"
                 << " | " << appliances[i].hours << " hrs"
                 << " | " << energyPerDay(appliances[i]) << " kWh/day\n";
            found = true;
        }
    }

    if (!found) {
        cout << "Appliance not found.\n";
    }
}

void showEnergySummary() {
    if (appliances.empty()) {
        cout << "No appliances available.\n";
        return;
    }

    cout << "\nEnergy Summary\n";

    for (int i = 0; i < appliances.size(); i++) {
        cout << appliances[i].name
             << " -> "
             << energyPerDay(appliances[i])
             << " kWh/day\n";
    }

    cout << "Total Energy = " << totalEnergyUsed() << " kWh/day\n";
}

void calculateBill() {
    if (appliances.empty()) {
        cout << "No appliances available.\n";
        return;
    }

    double costPerKWh;

    cout << "Enter cost per kWh: ";
    cin >> costPerKWh;

    if (cin.fail()) {
        clearBadInput();
        cout << "Invalid cost input.\n";
        return;
    }

    double totalEnergy = totalEnergyUsed();
    double totalBill = totalEnergy * costPerKWh;

    cout << "\nTotal Energy: " << totalEnergy << " kWh/day\n";
    cout << "Electricity Bill: " << totalBill << endl;
}

int main() {
    loadFromFile();

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
            viewAppliances();
        } else if (choice == 3) {
            searchAppliance();
        } else if (choice == 4) {
            showEnergySummary();
        } else if (choice == 5) {
            calculateBill();
        } else if (choice == 0) {
            cout << "Goodbye\n";
        } else {
            cout << "Invalid choice\n";
        }

    } while (choice != 0);

    return 0;
}
