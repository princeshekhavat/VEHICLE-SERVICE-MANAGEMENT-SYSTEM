#ifndef SERVICERECORD_H
#define SERVICERECORD_H

#include "Entity.h"

class ServiceRecord : public Entity {
private:
    int vehicleId;
    std::string serviceType;
    double cost;
    std::string date;
    std::string status;   // Pending, In Progress, Completed

public:
    ServiceRecord();
    ServiceRecord(int id, int vehicleId, const std::string& serviceType,
                  double cost, const std::string& date, const std::string& status);

    int getVehicleId() const;
    double getCost() const;
    const std::string& getStatus() const;
    void setStatus(const std::string& newStatus);

    void display() const override;
    std::string serialize() const override;
    static ServiceRecord deserialize(const std::string& line);
};

#endif
