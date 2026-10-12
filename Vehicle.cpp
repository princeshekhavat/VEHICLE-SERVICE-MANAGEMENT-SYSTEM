#include "Vehicle.h"
#include <iostream>
#include <iomanip>

Vehicle::Vehicle() : Entity(0) {}

Vehicle::Vehicle(int id, const std::string& regNo, const std::string& ownerName,
                 const std::string& phone, const std::string& model)
    : Entity(id), regNo(regNo), ownerName(ownerName), phone(phone), model(model) {}

const std::string& Vehicle::getRegNo() const { return regNo; }
const std::string& Vehicle::getOwnerName() const { return ownerName; }

void Vehicle::display() const {
    std::cout << std::left
              << std::setw(5)  << id
              << std::setw(14) << regNo
              << std::setw(18) << ownerName
              << std::setw(13) << phone
              << model << "\n";
}

std::string Vehicle::serialize() const {
    return std::to_string(id) + "|" + regNo + "|" + ownerName + "|" + phone + "|" + model;
}

Vehicle Vehicle::deserialize(const std::string& line) {
    std::vector<std::string> p = splitLine(line, '|');
    if (p.size() < 5) return Vehicle();
    return Vehicle(std::stoi(p[0]), p[1], p[2], p[3], p[4]);
}
