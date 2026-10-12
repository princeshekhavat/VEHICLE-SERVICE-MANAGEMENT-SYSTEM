#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include <vector>
#include "Vehicle.h"
#include "ServiceRecord.h"

// Handles saving and loading of data so records persist between runs
class FileManager {
public:
    static bool saveVehicles(const std::vector<Vehicle>& vehicles, const std::string& path);
    static std::vector<Vehicle> loadVehicles(const std::string& path);

    static bool saveServices(const std::vector<ServiceRecord>& services, const std::string& path);
    static std::vector<ServiceRecord> loadServices(const std::string& path);
};

#endif
