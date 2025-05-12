#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

// Max number of investments
const int MAX = 100;

// Arrays to hold investment data
string types[MAX];
float amounts[MAX];
float rates[MAX];
int durations[MAX];
float rois[MAX];
int totalInvestments = 0;

// Function to calculate compound ROI percentage
float calculateROI(float amount, float rate, int years) {
    float finalValue = amount * pow(1 + rate / 100, years);
    float roi = ((finalValue - amount) / amount) * 100;
    return roi;
}

// Add a new investment
void addInvestment() {
    if (totalInvestments >= MAX) {
        cout << "Portfolio full. Cannot add more investments.\n";
        return;
    }

    cout << "\nSelect Investment Type:\n";
    cout << "1. Fixed Deposit (FD)\n";
    cout << "2. Mutual Fund\n";
    cout << "3. Stock\n";
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;

    string type;
    switch (choice) {
        case 1: type = "Fixed Deposit"; break;
        case 2: type = "Mutual Fund"; break;
        case 3: type = "Stock"; break;
        default:
            cout << "Invalid choice.\n";
            return;
    }

    float amount, rate;
    int duration;
    cout << "Enter investment amount: $";
    cin >> amount;
    cout << "Enter expected annual return rate (%): ";
    cin >> rate;
    cout << "Enter duration (in years): ";
    cin >> duration;

    float roi = calculateROI(amount, rate, duration);

    types[totalInvestments] = type;
    amounts[totalInvestments] = amount;
    rates[totalInvestments] = rate;
    durations[totalInvestments] = duration;
    rois[totalInvestments] = roi;

    totalInvestments++;
    cout << "? Investment added successfully!\n\n";
}

// View portfolio summary
void viewSummary() {
    if (totalInvestments == 0) {
        cout << "No investments added yet.\n";
        return;
    }

    float totalAmount = 0, totalFinal = 0;
    cout << "\n---------- Portfolio Summary ----------\n";
    for (int i = 0; i < totalInvestments; i++) {
        float finalValue = amounts[i] * pow(1 + rates[i] / 100, durations[i]);
        totalAmount += amounts[i];
        totalFinal += finalValue;

        cout << "\nInvestment #" << i + 1 << ":\n";
        cout << "Type       : " << types[i] << "\n";
        cout << "Amount     : $" << fixed << setprecision(2) << amounts[i] << "\n";
        cout << "Rate       : " << rates[i] << "%\n";
        cout << "Duration   : " << durations[i] << " years\n";
        cout << "ROI        : " << fixed << setprecision(2) << rois[i] << "%\n";
        cout << "Final Value: $" << fixed << setprecision(2) << finalValue << "\n";
    }

    float avgROI = totalInvestments > 0 ? (totalFinal - totalAmount) / totalAmount * 100 : 0;
    cout << "\n----------------------------------------\n";
    cout << "Total Invested Amount: $" << totalAmount << "\n";
    cout << "Total Portfolio Value: $" << totalFinal << "\n";
    cout << "Average ROI          : " << avgROI << "%\n";
    cout << "----------------------------------------\n\n";
}

void deleteInvestment() {
    if (totalInvestments == 0) {
        cout << "No investments to delete.\n";
        return;
    }

    viewSummary(); // Show investments so user can choose
    cout << "\nEnter the investment number to delete (1 to " << totalInvestments << "): ";
    int index;
    cin >> index;

    if (index < 1 || index > totalInvestments) {
        cout << "Invalid investment number.\n";
        return;
    }

    index--; // Convert to 0-based index

    // Shift all arrays one step left
    for (int i = index; i < totalInvestments - 1; i++) {
        types[i] = types[i + 1];
        amounts[i] = amounts[i + 1];
        rates[i] = rates[i + 1];
        durations[i] = durations[i + 1];
        rois[i] = rois[i + 1];
    }

    totalInvestments--;
    cout << "? Investment deleted successfully!\n";
}

void sortByROI() {
    if (totalInvestments < 2) {
        cout << "Not enough investments to sort.\n";
        return;
    }

    // Bubble Sort by ROI (descending)
    for (int i = 0; i < totalInvestments - 1; i++) {
        for (int j = 0; j < totalInvestments - i - 1; j++) {
            if (rois[j] < rois[j + 1]) {
                // Swap ROI
                swap(rois[j], rois[j + 1]);
                // Swap other arrays accordingly
                swap(types[j], types[j + 1]);
                swap(amounts[j], amounts[j + 1]);
                swap(rates[j], rates[j + 1]);
                swap(durations[j], durations[j + 1]);
            }
        }
    }

    cout << "? Investments sorted by ROI (highest to lowest).\n\n";
    viewSummary(); // Optional: display updated summary
}

void showPortfolioValue() {
    if (totalInvestments == 0) {
        cout << "No investments in portfolio.\n";
        return;
    }

    float totalInvested = 0, totalReturn = 0;

    for (int i = 0; i < totalInvestments; i++) {
        totalInvested += amounts[i];
        totalReturn += amounts[i] * (rois[i] / 100.0);
    }

    float finalValue = totalInvested + totalReturn;
    float overallROI = (totalReturn / totalInvested) * 100;

    cout << fixed << setprecision(2);
    cout << "\n------ Portfolio Summary ------\n";
    cout << "Total Invested Amount : $" << totalInvested << "\n";
    cout << "Total ROI Earned      : $" << totalReturn << "\n";
    cout << "Final Portfolio Value : $" << finalValue << "\n";
    cout << "Overall Portfolio ROI : " << overallROI << "%\n";
    cout << "-------------------------------\n";
}




// Main menu
void showMenu() {
    cout << "----------------------------------------\n";
    cout << "     Investment Portfolio Tracker\n";
    cout << "----------------------------------------\n";
    cout << "1. Add New Investment\n";
    cout << "2. View Portfolio Summary\n";
    cout << "3. Sort Investments by ROI (High to Low)\n";
    cout << "4. View Total vs. Final Portfolio Value\n";
	cout << "5. Delete an Investment\n";
    cout << "6. Exit\n";
    cout << "Enter your choice: ";
   
}

int main() {
    int choice;
    do {
        showMenu();
        cin >> choice;
        switch (choice) {
            case 1: addInvestment(); break;
            case 2: viewSummary(); break;
            case 3: cout << "Exiting. Goodbye!\n"; break;
            case 4: deleteInvestment(); break;
            case 5: sortByROI(); break;
            case 6: showPortfolioValue(); break;
            default: cout << "Invalid option. Try again.\n";
        }
    } while (choice != 3);

    return 0;
}
