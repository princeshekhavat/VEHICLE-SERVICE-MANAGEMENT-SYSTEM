#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <vector>
#include <sstream>

// Splits a line by a delimiter (used when reading records from files)
inline std::vector<std::string> splitLine(const std::string& line, char delim) {
    std::vector<std::string> parts;
    std::string item;
    std::stringstream ss(line);
    while (std::getline(ss, item, delim)) parts.push_back(item);
    return parts;
}

// Abstract base class for everything stored by the system
class Entity {
protected:
    int id;

public:
    explicit Entity(int id = 0);
    virtual ~Entity();

    int getId() const;
    void setId(int newId);

    virtual void display() const = 0;
    virtual std::string serialize() const = 0;
};

#endif
