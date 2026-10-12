#ifndef SERVICECENTER_H
#define SERVICECENTER_H

#include <string>
#include <vector>
#include "Vehicle.h"
#include "ServiceRecord.h"

// Core class: manages vehicles and their service records
class ServiceCenter {
private:
    std::vector<Vehicle> vehicles;
    std::vector<ServiceRecord> services;
    int nextVehicleId;
    int nextServiceId;

    std::string vehicleFile;
    std::string serviceFile;

    int findVehicleIndexById(int id) const;

public:
    ServiceCenter(const std::string& vehicleFile, const std::string& serviceFile);

    void loadData();
    void saveData() const;

    void addVehicle(const std::string& regNo, const std::string& owner,
                    const std::string& phone, const std::string& model);
    void viewVehicles() const;
    void searchVehicle(const std::string& regNo) const;
    void deleteVehicle(int id);

    void bookService(int vehicleId, const std::string& type, double cost, const std::string& date);
    void viewServices() const;
    void updateServiceStatus(int serviceId, const std::string& status);
    void generateBill(int vehicleId) const;
};

#endif
