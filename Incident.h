#pragma once

#include <string>

class Incident {
private:
    std::string area;
    std::string type;
    std::string date;

public:
    Incident();
    Incident(const std::string& area, const std::string& type, const std::string& date);

    std::string getArea() const;
    std::string getType() const;
    std::string getDate() const;

    void setArea(const std::string& newArea);
    void setType(const std::string& newType);
    void setDate(const std::string& newDate);

    static bool validateDate(const std::string& date);
};
