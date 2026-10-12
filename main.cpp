#include <iostream>
#include <string>
#include "ServiceCenter.h"

// Reads a whole line safely
static std::string readLine(const std::string& prompt) {
    std::string s;
    std::cout << prompt;
    std::getline(std::cin, s);
    return s;
}

static int readInt(const std::string& prompt) {
    while (true) {
        std::string s = readLine(prompt);
        try { return std::stoi(s); }
        catch (...) { std::cout << "Please enter a valid number.\n"; }
    }
}

static double readDouble(const std::string& prompt) {
    while (true) {
        std::string s = readLine(prompt);
        try { return std::stod(s); }
        catch (...) { std::cout << "Please enter a valid amount.\n"; }
    }
}

static void showMenu() {
    std::cout << "\n===== VEHICLE SERVICE MANAGEMENT SYSTEM =====\n"
              << "1. Register Vehicle\n"
              << "2. View All Vehicles\n"
              << "3. Search Vehicle by Registration No\n"
              << "4. Delete Vehicle\n"
              << "5. Book Service\n"
              << "6. View All Services\n"
              << "7. Update Service Status\n"
              << "8. Generate Bill\n"
              << "0. Save and Exit\n"
              << "Enter choice: ";
}

int main() {
    ServiceCenter center("data/vehicles.txt", "data/services.txt");
    center.loadData();

    int choice;
    do {
        showMenu();
        std::string line;
        if (!std::getline(std::cin, line)) break;
        try { choice = std::stoi(line); } catch (...) { choice = -1; }

        switch (choice) {
            case 1: {
                std::string reg   = readLine("Registration No: ");
                std::string owner = readLine("Owner Name: ");
                std::string phone = readLine("Phone: ");
                std::string model = readLine("Vehicle Model: ");
                center.addVehicle(reg, owner, phone, model);
                break;
            }
            case 2: center.viewVehicles(); break;
            case 3: center.searchVehicle(readLine("Registration No: ")); break;
            case 4: center.deleteVehicle(readInt("Vehicle ID to delete: ")); break;
            case 5: {
                int vid = readInt("Vehicle ID: ");
                std::string type = readLine("Service Type (e.g. Oil Change): ");
                double cost = readDouble("Estimated Cost: ");
                std::string date = readLine("Date (DD-MM-YYYY): ");
                center.bookService(vid, type, cost, date);
                break;
            }
            case 6: center.viewServices(); break;
            case 7: {
                int sid = readInt("Service ID: ");
                std::cout << "1. Pending  2. In Progress  3. Completed\n";
                int st = readInt("New status: ");
                const char* names[] = {"Pending", "In Progress", "Completed"};
                if (st >= 1 && st <= 3) center.updateServiceStatus(sid, names[st - 1]);
                else std::cout << "Invalid status option.\n";
                break;
            }
            case 8: center.generateBill(readInt("Vehicle ID: ")); break;
            case 0: center.saveData(); std::cout << "Data saved. Goodbye!\n"; break;
            default: std::cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);

    return 0;
}
