#ifndef VEHICLE_H
#define VEHICLE_H

#include "Entity.h"

class Vehicle : public Entity {
private:
    std::string regNo;
    std::string ownerName;
    std::string phone;
    std::string model;

public:
    Vehicle();
    Vehicle(int id, const std::string& regNo, const std::string& ownerName,
            const std::string& phone, const std::string& model);

    const std::string& getRegNo() const;
    const std::string& getOwnerName() const;

    void display() const override;
    std::string serialize() const override;
    static Vehicle deserialize(const std::string& line);
};

#endif
