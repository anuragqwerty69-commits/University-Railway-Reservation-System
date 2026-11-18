#pragma once
#include <string>

class Train {
    int number_;
    std::string name_;
    std::string source_;
    std::string destination_;
    std::string departure_;
    int capacity_;
    double fare_;
public:
    Train(int number, std::string name, std::string source, std::string destination,
          std::string departure, int capacity, double fare);
    int getNumber() const;
    const std::string& getName() const;
    const std::string& getSource() const;
    const std::string& getDestination() const;
    const std::string& getDeparture() const;
    int getCapacity() const;
    double getFare() const;
    void display() const;
};
