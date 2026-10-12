#include "ServiceRecord.h"
#include <iostream>
#include <iomanip>

ServiceRecord::ServiceRecord() : Entity(0), vehicleId(0), cost(0.0) {}

ServiceRecord::ServiceRecord(int id, int vehicleId, const std::string& serviceType,
                             double cost, const std::string& date, const std::string& status)
    : Entity(id), vehicleId(vehicleId), serviceType(serviceType),
      cost(cost), date(date), status(status) {}

int ServiceRecord::getVehicleId() const { return vehicleId; }
double ServiceRecord::getCost() const { return cost; }
const std::string& ServiceRecord::getStatus() const { return status; }
void ServiceRecord::setStatus(const std::string& newStatus) { status = newStatus; }

void ServiceRecord::display() const {
    std::cout << std::left
              << std::setw(5)  << id
              << std::setw(10) << vehicleId
              << std::setw(24) << serviceType
              << std::setw(12) << std::fixed << std::setprecision(2) << cost
              << std::setw(13) << date
              << status << "\n";
}

std::string ServiceRecord::serialize() const {
    return std::to_string(id) + "|" + std::to_string(vehicleId) + "|" + serviceType + "|" +
           std::to_string(cost) + "|" + date + "|" + status;
}

ServiceRecord ServiceRecord::deserialize(const std::string& line) {
    std::vector<std::string> p = splitLine(line, '|');
    if (p.size() < 6) return ServiceRecord();
    return ServiceRecord(std::stoi(p[0]), std::stoi(p[1]), p[2], std::stod(p[3]), p[4], p[5]);
}
