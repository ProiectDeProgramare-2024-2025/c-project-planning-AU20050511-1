#include "IncidentManager.h"
#include "Colors.h"
#include <iostream>
#include "Utils.h"

int main(int argc, char* argv[]) {
    IncidentManager manager;
    manager.loadFromFile("incidents.txt");

    std::string input;
    int choice;

    while (true) {
        clear();
        std::cout << GREEN << "=== Incident Reporting - Main 2 ===" << RESET << "\n";
        std::cout << "1. Filter Incidents\n";
        std::cout << "2. Edit Incident\n";
        std::cout << "3. Delete Incident\n";
        std::cout << "4. Sort Incidents\n";
        std::cout << "5. Exit\n";
        std::cout << "Choose an option: ";
        std::getline(std::cin, input);

        try {
            choice = std::stoi(input);
        }
        catch (...) {
            std::cout << RED << "Invalid input. Try again." << RESET << "\n";
            std::cin.get();
            continue;
        }

        switch (choice) {
        case 1:
            manager.filterIncidents();
            break;
        case 2:
            manager.editIncident();
            break;
        case 3:
            manager.deleteIncident();
            break;
        case 4:
            manager.sortIncidents();
            break;
        case 5:
            clear();
            std::cout << GREEN << "Exiting Main 2... Goodbye!" << RESET << "\n";
            return 0;
        default:
            std::cout << RED << "Invalid choice!" << RESET << "\n";
            std::cin.get();
        }
    }
}
