#include "Utils.h"
#include <iostream>
#include <sstream>
#include <cstdlib>
#ifdef _WIN32
#define CLEAR_COMMAND "cls"
#else
#define CLEAR_COMMAND "clear"
#endif

void clear() {
    system(CLEAR_COMMAND);
}
bool validateDate(const std::string& date) {
    if (date.length() != 10 || date[2] != '.' || date[5] != '.')
        return false;

    int day, month, year;
    if (sscanf_s(date.c_str(), "%2d.%2d.%4d", &day, &month, &year) != 3)
        return false;

    if (year < 1900 || month < 1 || month > 12 || day < 1)
        return false;

    int days_in_month[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
        days_in_month[1] = 29;

    return day <= days_in_month[month - 1];
}

void getValidInput(const std::string& prompt, std::string& input, size_t maxLen) {
    do {
        std::cout << prompt;
        std::getline(std::cin, input);

        if (input.empty())
            std::cout << "\u274C Input cannot be empty!\n";
        else if (input.length() > maxLen) {
            std::cout << "\u274C Input too long! Max length: " << maxLen << "\n";
            input.clear();
        }
    } while (input.empty());
}

void getValidDate(const std::string& prompt, std::string& date) {
    do {
        std::cout << prompt;
        std::getline(std::cin, date);

        if (!validateDate(date))
            std::cout << "\u274C Invalid date format or logical date! Use dd.mm.yyyy.\n";
    } while (!validateDate(date));
}