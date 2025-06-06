#include "IncidentManager.h"
#include "Colors.h"
#include <iostream>
#include "Utils.h"

#ifdef _WIN32
#define CLEAR_COMMAND "cls"
#else
#define CLEAR_COMMAND "clear"
#endif


int main(int argc, char* argv[]) {
    IncidentManager manager;
    manager.loadFromFile("incidents.txt");

    std::string line;
    int choice;

    while (true) {
        clear();
        std::cout << "=== " << GREEN << "Incident Reporting - Main 1" << RESET << " ===\n";
        std::cout << "1. Add Incident\n";
        std::cout << "2. View Incidents\n";
        std::cout << "3. Exit\n";
        std::cout << "Choose an option: ";
        std::getline(std::cin, line);

        try {
            choice = std::stoi(line);
        }
        catch (...) {
            std::cout << RED << "Invalid input. Press Enter to try again." << RESET;
            std::cin.get();
            continue;
        }

        switch (choice) {
        case 1:
            manager.addIncident();
            break;
        case 2:
            manager.viewIncidents();
            break;
        case 3:
            clear();
            std::cout << GREEN << "Exiting Main 1... Goodbye!" << RESET << std::endl;
            return 0;
        default:
            std::cout << RED << "Invalid choice. Press Enter to try again." << RESET;
            std::cin.get();
        }
    }
}
