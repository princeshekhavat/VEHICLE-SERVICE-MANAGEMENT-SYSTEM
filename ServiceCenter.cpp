#include "ServiceCenter.h"
#include "FileManager.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

ServiceCenter::ServiceCenter(const std::string& vehicleFile, const std::string& serviceFile)
    : nextVehicleId(1), nextServiceId(1), vehicleFile(vehicleFile), serviceFile(serviceFile) {}

int ServiceCenter::findVehicleIndexById(int id) const {
    for (size_t i = 0; i < vehicles.size(); ++i)
        if (vehicles[i].getId() == id) return static_cast<int>(i);
    return -1;
}

void ServiceCenter::loadData() {
    vehicles = FileManager::loadVehicles(vehicleFile);
    services = FileManager::loadServices(serviceFile);
    for (const auto& v : vehicles) nextVehicleId = std::max(nextVehicleId, v.getId() + 1);
    for (const auto& s : services) nextServiceId = std::max(nextServiceId, s.getId() + 1);
}

void ServiceCenter::saveData() const {
    if (!FileManager::saveVehicles(vehicles, vehicleFile) ||
        !FileManager::saveServices(services, serviceFile))
        std::cout << "Warning: could not save data to file.\n";
}

void ServiceCenter::addVehicle(const std::string& regNo, const std::string& owner,
                               const std::string& phone, const std::string& model) {
    for (const auto& v : vehicles) {
        if (v.getRegNo() == regNo) {
            std::cout << "A vehicle with this registration number already exists.\n";
            return;
        }
    }
    vehicles.emplace_back(nextVehicleId, regNo, owner, phone, model);
    std::cout << "Vehicle added successfully. Vehicle ID: " << nextVehicleId << "\n";
    ++nextVehicleId;
}

void ServiceCenter::viewVehicles() const {
    if (vehicles.empty()) { std::cout << "No vehicles registered.\n"; return; }
    std::cout << std::left << std::setw(5) << "ID" << std::setw(14) << "Reg No"
              << std::setw(18) << "Owner" << std::setw(13) << "Phone" << "Model\n";
    std::cout << std::string(60, '-') << "\n";
    for (const auto& v : vehicles) v.display();
}

void ServiceCenter::searchVehicle(const std::string& regNo) const {
    for (const auto& v : vehicles) {
        if (v.getRegNo() == regNo) {
            std::cout << "Vehicle found:\n";
            v.display();
            return;
        }
    }
    std::cout << "No vehicle found with registration number " << regNo << ".\n";
}

void ServiceCenter::deleteVehicle(int id) {
    int idx = findVehicleIndexById(id);
    if (idx == -1) { std::cout << "Vehicle ID not found.\n"; return; }
    vehicles.erase(vehicles.begin() + idx);
    services.erase(std::remove_if(services.begin(), services.end(),
                   [id](const ServiceRecord& s) { return s.getVehicleId() == id; }),
                   services.end());
    std::cout << "Vehicle and its service records deleted.\n";
}

void ServiceCenter::bookService(int vehicleId, const std::string& type, double cost,
                                const std::string& date) {
    if (findVehicleIndexById(vehicleId) == -1) {
        std::cout << "Vehicle ID not found. Register the vehicle first.\n";
        return;
    }
    services.emplace_back(nextServiceId, vehicleId, type, cost, date, "Pending");
    std::cout << "Service booked. Service ID: " << nextServiceId << "\n";
    ++nextServiceId;
}

void ServiceCenter::viewServices() const {
    if (services.empty()) { std::cout << "No service records.\n"; return; }
    std::cout << std::left << std::setw(5) << "ID" << std::setw(10) << "Vehicle"
              << std::setw(24) << "Service" << std::setw(12) << "Cost"
              << std::setw(13) << "Date" << "Status\n";
    std::cout << std::string(70, '-') << "\n";
    for (const auto& s : services) s.display();
}

void ServiceCenter::updateServiceStatus(int serviceId, const std::string& status) {
    for (auto& s : services) {
        if (s.getId() == serviceId) {
            s.setStatus(status);
            std::cout << "Service status updated to: " << status << "\n";
            return;
        }
    }
    std::cout << "Service ID not found.\n";
}

void ServiceCenter::generateBill(int vehicleId) const {
    int idx = findVehicleIndexById(vehicleId);
    if (idx == -1) { std::cout << "Vehicle ID not found.\n"; return; }

    double subtotal = 0.0;
    std::cout << "\n========== SERVICE BILL ==========\n";
    std::cout << "Vehicle : " << vehicles[idx].getRegNo()
              << " (" << vehicles[idx].getOwnerName() << ")\n";
    std::cout << "----------------------------------\n";
    for (const auto& s : services) {
        if (s.getVehicleId() == vehicleId && s.getStatus() == "Completed") {
            s.display();
            subtotal += s.getCost();
        }
    }
    if (subtotal == 0.0) {
        std::cout << "No completed services to bill.\n";
        return;
    }
    double gst = subtotal * 0.18;
    std::cout << "----------------------------------\n";
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Subtotal  : " << subtotal << "\n";
    std::cout << "GST (18%) : " << gst << "\n";
    std::cout << "Total     : " << subtotal + gst << "\n";
    std::cout << "==================================\n";
}
