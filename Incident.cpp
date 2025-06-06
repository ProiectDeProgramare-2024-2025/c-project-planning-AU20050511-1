#define _CRT_SECURE_NO_WARNINGS
#include "Incident.h"
#include <regex>
#include <sstream>

Incident::Incident() {}

Incident::Incident(const std::string& area, const std::string& type, const std::string& date)
    : area(area), type(type), date(date) {
}

std::string Incident::getArea() const {
    return area;
}

std::string Incident::getType() const {
    return type;
}

std::string Incident::getDate() const {
    return date;
}

void Incident::setArea(const std::string& newArea) {
    area = newArea;
}

void Incident::setType(const std::string& newType) {
    type = newType;
}

void Incident::setDate(const std::string& newDate) {
    date = newDate;
}

bool Incident::validateDate(const std::string& date) {
    if (date.length() != 10 || date[2] != '.' || date[5] != '.')
        return false;

    int day, month, year;
    if (sscanf_s(date.c_str(), "%2d.%2d.%4d", &day, &month, &year) != 3)
        return false;

    if (year < 1900 || month < 1 || month > 12 || day < 1)
        return false;

    int days_in_month[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    bool is_leap = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
    if (is_leap)
        days_in_month[1] = 29;

    return day <= days_in_month[month - 1];
}