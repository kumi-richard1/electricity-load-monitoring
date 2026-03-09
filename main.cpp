#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>

using namespace std;

const string APPLIANCE_FILE = "appliances.txt";
const string BILL_FILE = "billing_summary.txt";

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

double energyPerDay(const Appliance& appliance) {
    return (appliance.power * appliance.hours) / 1000.0;
}

string makeLowercase(string text) {
    for (int i = 0; i < text.size(); i++) {
        if (text[i] >= 'A' && text[i] <= 'Z') {
            text[i] = text[i] + 32;
        }
    }
    return text;
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

void displayMenu() {
    cout << "\n=================================\n";
    cout << " Electrical Load Monitoring System\n";
    cout << "=================================\n";
    cout << "1. Register appliance\n";
    cout << "2. View appliances\n";
    cout << "3. Search appliance\n";
    cout << "4. Energy summary\n";
    cout << "5. Calculate electricity bill\n";
    cout << "0. Exit\n";
    cout << "Enter your choice: ";
}

void addAppliance() {
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

    cout << "Enter hours used per day: ";
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

void displayAppliances() {
    if (appliances.empty()) {
        cout << "No appliances registered.\n";
        return;
    }

    cout << "\nRegistered Appliances\n";
    cout << "--------------------------\n";

    for (int i = 0; i < appliances.size(); i++) {
        cout << i + 1 << ". " << appliances[i].name
             << " | " << appliances[i].power << " W"
             << " | " << appliances[i].hours << " hrs/day\n";
    }
}

void findAppliance() {
    if (appliances.empty()) {
        cout << "No appliances available.\n";
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string keyword;
    cout << "Enter appliance name: ";
    getline(cin, keyword);

    keyword = makeLowercase(keyword);

    bool found = false;

    for (int i = 0; i < appliances.size(); i++) {
        string storedName = makeLowercase(appliances[i].name);

        if (storedName.find(keyword) != string::npos) {
            cout << appliances[i].name
                 << " | " << appliances[i].power << " W"
                 << " | " << appliances[i].hours << " hrs"
                 << " | " << energyPerDay(appliances[i]) << " kWh/day\n";
            found = true;
        }
    }

    if (!found) {
        cout << "Appliance not found.\n";
    }
}

double totalEnergyUsed() {
    double total = 0;

    for (int i = 0; i < appliances.size(); i++) {
        total = total + energyPerDay(appliances[i]);
    }

    return total;
}

void showEnergySummary() {
    if (appliances.empty()) {
        cout << "No appliances available.\n";
        return;
    }

    cout << "\nEnergy Summary\n";
    cout << "--------------------------\n";

    for (int i = 0; i < appliances.size(); i++) {
        cout << appliances[i].name
             << " -> "
             << energyPerDay(appliances[i])
             << " kWh/day\n";
    }

    cout << "Total Energy = " << totalEnergyUsed() << " kWh/day\n";
}

void generateBill() {
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
    double billAmount = totalEnergy * costPerKWh;

    cout << "\nTotal Energy: " << totalEnergy << " kWh/day\n";
    cout << "Electricity Bill: " << billAmount << endl;

    ofstream file(BILL_FILE);

    if (file.is_open()) {
        file << "Billing Summary\n";
        file << "========================\n";

        for (int i = 0; i < appliances.size(); i++) {
            file << appliances[i].name
                 << " -> "
                 << energyPerDay(appliances[i])
                 << " kWh/day\n";
        }

        file << "\nTotal Energy: " << totalEnergy << " kWh/day\n";
        file << "Total Bill: " << billAmount << endl;

        file.close();
    }

    cout << "Billing summary saved to billing_summary.txt\n";
}

int main() {
    loadFromFile();

    int choice;

    do {
        displayMenu();
        cin >> choice;

        if (cin.fail()) {
            clearBadInput();
            choice = -1;
        }

        switch (choice) {
            case 1:
                addAppliance();
                break;
            case 2:
                displayAppliances();
                break;
            case 3:
                findAppliance();
                break;
            case 4:
                showEnergySummary();
                break;
            case 5:
                generateBill();
                break;
            case 0:
                cout << "Goodbye\n";
                break;
            default:
                cout << "Invalid choice\n";
        }

    } while (choice != 0);

    return 0;
}
