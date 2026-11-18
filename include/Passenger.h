#pragma once
#include <string>

class Passenger {
    std::string name_;
    int age_;
    std::string gender_;
    std::string phone_;
public:
    Passenger(std::string name, int age, std::string gender, std::string phone);
    const std::string& getName() const;
    int getAge() const;
    const std::string& getGender() const;
    const std::string& getPhone() const;
};
