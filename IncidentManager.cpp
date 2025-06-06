#include "IncidentManager.h"
#include "Colors.h"
#include "Utils.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>

#ifdef _WIN32
#define CLEAR_COMMAND "cls"
#else
#define CLEAR_COMMAND "clear"
#endif

void IncidentManager::loadFromFile(const std::string& filename) {
    std::ifstream file(dataFile);
    if (!file) return;

    std::string line;
    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string area, type, date;

        getline(ss, area, ',');
        getline(ss, type, ',');
        getline(ss, date);

        if (!area.empty() && !type.empty() && !date.empty())
            incidents.push_back(Incident(area, type, date));
    }
}

void IncidentManager::filterIncidents() {
    system(CLEAR_COMMAND);

    std::cout << "=== Filter Incident Reports ===\n";
    std::cout << "1. Filter by Area\n";
    std::cout << "2. Filter by Incident Type\n";
    std::cout << "3. Filter by Date\n";
    std::cout << "4. Back to Menu\n";
    std::cout << "Choose an option: ";

    std::string input;
    std::getline(std::cin, input);

    if (input == "4") return;

    int option;
    try {
        option = std::stoi(input);
        if (option < 1 || option > 3) throw std::out_of_range("Invalid range");
    }
    catch (...) {
        std::cout << RED << "Invalid input. Try again." << RESET << "\n";
        std::cin.get();
        return;
    }

    std::string keyword;
    getValidInput("Enter search keyword: ", keyword);

    filterIncidentsByField(option, keyword);
}

void IncidentManager::saveToFile(const std::string& filename){
    std::ofstream file(dataFile);
    if (!file) {
        std::cout << RED << "Error saving file." << RESET << "\n";
        return;
    }
    for (const auto& inc : incidents)
        file << inc.getArea() << "," << inc.getType() << "," << inc.getDate() << "\n";
}

void IncidentManager::addIncident() {
    std::string area, type, date;
    getValidInput("Enter area: ", area);
    getValidInput("Enter type: ", type);
    getValidDate("Enter date (dd.mm.yyyy): ", date);
    incidents.push_back(Incident(area, type, date));
    saveToFile(dataFile);
    std::cout << GREEN << "Incident added successfully!" << RESET << std::endl;
    std::cin.get();
}

void IncidentManager::viewIncidents(bool pause) const {
    system(CLEAR_COMMAND);
    if (incidents.empty()) {
        std::cout << YELLOW << "No incidents reported yet." << RESET << "\n";
    }
    else {
        std::cout << "=== Incident Reports ===\n\n";
        std::cout << std::left << std::setw(4) << "#" << std::setw(20) << "Area"
            << std::setw(20) << "Incident Type" << std::setw(12) << "Date" << "\n";
        std::cout << std::string(60, '-') << "\n";
        for (size_t i = 0; i < incidents.size(); ++i) {
            std::cout << std::left << std::setw(4) << i + 1
                << BLUE << std::setw(20) << incidents[i].getArea() << RESET
                << YELLOW << std::setw(20) << incidents[i].getType() << RESET
                << GREEN << std::setw(12) << incidents[i].getDate() << RESET << "\n";
        }
    }
    if (pause) {
        std::cout << "\nPress Enter to return...";
        std::cin.get();
    }
}

void IncidentManager::filterIncidentsByField(int fieldOption, const std::string& keyword) const {
    std::string loweredKeyword = keyword;
    std::transform(loweredKeyword.begin(), loweredKeyword.end(), loweredKeyword.begin(), ::tolower);

    std::vector<Incident> filtered;
    for (const auto& inc : incidents) {
        std::string value;
        if (fieldOption == 1) value = inc.getArea();
        else if (fieldOption == 2) value = inc.getType();
        else if (fieldOption == 3) value = inc.getDate();

        std::string lowered = value;
        std::transform(lowered.begin(), lowered.end(), lowered.begin(), ::tolower);

        if (lowered.find(loweredKeyword) != std::string::npos)
            filtered.push_back(inc);
    }

    system(CLEAR_COMMAND);
    std::cout << "=== Filtered Results ===\n";
    if (filtered.empty()) {
        std::cout << RED << "No matching incidents found." << RESET << "\n";
    }
    else {
        for (size_t i = 0; i < filtered.size(); ++i) {
            std::cout << std::left << std::setw(4) << i + 1
                << BLUE << std::setw(20) << filtered[i].getArea() << RESET
                << YELLOW << std::setw(20) << filtered[i].getType() << RESET
                << GREEN << std::setw(12) << filtered[i].getDate() << RESET << "\n";
        }
    }
    std::cout << "\nPress Enter to return...";
    std::cin.get();
}

void IncidentManager::editIncident() {
    if (incidents.empty()) {
        std::cout << YELLOW << "No incidents to edit." << RESET << "\n";
        std::cin.get();
        return;
    }

    viewIncidents(false);
    std::cout << "\nEnter incident number to edit (0 to return): ";
    std::string input;
    std::getline(std::cin, input);

    int index;
    try {
        index = std::stoi(input);
    }
    catch (...) {
        std::cout << RED << "Invalid input!" << RESET << "\n";
        std::cin.get();
        return;
    }

    if (index == 0) return;
    if (index < 1 || static_cast<size_t>(index) > incidents.size()) {
        std::cout << RED << "Invalid incident number." << RESET << "\n";
        std::cin.get();
        return;
    }

    Incident& inc = incidents[index - 1];
    while (true) {
        system(CLEAR_COMMAND);
        std::cout << "=== Edit Incident #" << index << " ===\n";
        std::cout << "Current Data: " << BLUE << inc.getArea() << RESET << " | "
            << YELLOW << inc.getType() << RESET << " | "
            << GREEN << inc.getDate() << RESET << "\n\n";

        std::cout << "1. Edit Area\n";
        std::cout << "2. Edit Incident Type\n";
        std::cout << "3. Edit Date\n";
        std::cout << "4. Back\n";
        std::cout << "Choose an option: ";

        std::string choice;
        std::getline(std::cin, choice);

        if (choice == "1") {
            std::string newVal;
            getValidInput("New area: ", newVal);
            inc.setArea(newVal);
        }
        else if (choice == "2") {
            std::string newVal;
            getValidInput("New incident type: ", newVal);
            inc.setType(newVal);
        }
        else if (choice == "3") {
            std::string newDate;
            getValidDate("New date (dd.mm.yyyy): ", newDate);
            inc.setDate(newDate);
        }
        else if (choice == "4") {
            break;
        }
        else {
            std::cout << RED << "Invalid option." << RESET << std::endl;
            std::cin.get();
            continue;
        }

        saveToFile(dataFile);
        std::cout << GREEN << "\u2705 Field updated!" << RESET << std::endl;
        std::cin.get();
    }
}

void IncidentManager::deleteIncident() {
    if (incidents.empty()) {
        std::cout << YELLOW << "No incidents to delete." << RESET << "\n";
        std::cin.get();
        return;
    }

    viewIncidents(false);
    std::cout << "\nEnter incident number to delete (0 to return): ";
    std::string input;
    std::getline(std::cin, input);

    int index;
    try {
        index = std::stoi(input);
    }
    catch (...) {
        std::cout << RED << "Invalid input!" << RESET << "\n";
        std::cin.get();
        return;
    }

    if (index == 0) return;
    if (index < 1 || static_cast<size_t>(index) > incidents.size()) {
        std::cout << RED << "Invalid incident number." << RESET << "\n";
        std::cin.get();
        return;
    }

    incidents.erase(incidents.begin() + (index - 1));
    saveToFile(dataFile);
    std::cout << GREEN << "\u2705 Incident deleted successfully!" << RESET << "\n";
    std::cin.get();
}

void IncidentManager::sortByArea() {
    std::sort(incidents.begin(), incidents.end(), [](const Incident& a, const Incident& b) {
        return a.getArea() < b.getArea();
        });
    saveToFile(dataFile);
}

void IncidentManager::sortByDate() {
    std::sort(incidents.begin(), incidents.end(), [](const Incident& a, const Incident& b) {
        return a.getDate() < b.getDate();
        });
    saveToFile(dataFile);
}

void IncidentManager::sortIncidents() {
    std::string input;
    int choice;

    std::cout << "=== Sort Incidents ===\n";
    std::cout << "1. Sort by Area\n";
    std::cout << "2. Sort by Date\n";
    std::cout << "3. Back\n";
    std::cout << "Choose an option: ";
    std::getline(std::cin, input);

    try {
        choice = std::stoi(input);
    }
    catch (...) {
        std::cout << RED << "Invalid input!\n" << RESET;
        std::cin.get();
        return;
    }

    switch (choice) {
    case 1:
        sortByArea();
        std::cout << GREEN << "Sorted by area.\n" << RESET;
        break;
    case 2:
        sortByDate();
        std::cout << GREEN << "Sorted by date.\n" << RESET;
        break;
    case 3:
        return;
    default:
        std::cout << RED << "Invalid option.\n" << RESET;
    }

    std::cin.get();
}

size_t IncidentManager::getIncidentCount() const {
    return incidents.size();
}

const Incident& IncidentManager::getIncident(size_t index) const {
    return incidents.at(index);
}
