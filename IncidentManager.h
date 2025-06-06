#pragma once

#include "Incident.h"
#include <vector>
#include <string>

class IncidentManager {
private:
    std::vector<Incident> incidents;
    std::string dataFile = "incidents.txt";

public:
    void loadFromFile(const std::string& filename);
    void saveToFile(const std::string& filename);

    void addIncident();
    void viewIncidents(bool pause = true) const;
    void filterIncidentsByField(int fieldOption, const std::string& keyword) const;
    void filterIncidents();
    void sortIncidents();

    void editIncident();
    void deleteIncident();

    void sortByArea();
    void sortByDate();

    size_t getIncidentCount() const;
    const Incident& getIncident(size_t index) const;
};
