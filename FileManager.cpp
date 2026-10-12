#include "FileManager.h"
#include <fstream>

bool FileManager::saveVehicles(const std::vector<Vehicle>& vehicles, const std::string& path) {
    std::ofstream out(path);
    if (!out) return false;
    for (const auto& v : vehicles) out << v.serialize() << "\n";
    return true;
}

std::vector<Vehicle> FileManager::loadVehicles(const std::string& path) {
    std::vector<Vehicle> list;
    std::ifstream in(path);
    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        Vehicle v = Vehicle::deserialize(line);
        if (v.getId() != 0) list.push_back(v);
    }
    return list;
}

bool FileManager::saveServices(const std::vector<ServiceRecord>& services, const std::string& path) {
    std::ofstream out(path);
    if (!out) return false;
    for (const auto& s : services) out << s.serialize() << "\n";
    return true;
}

std::vector<ServiceRecord> FileManager::loadServices(const std::string& path) {
    std::vector<ServiceRecord> list;
    std::ifstream in(path);
    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        ServiceRecord s = ServiceRecord::deserialize(line);
        if (s.getId() != 0) list.push_back(s);
    }
    return list;
}
