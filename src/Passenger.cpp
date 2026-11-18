#include "Passenger.h"
#include "Exceptions.h"
#include <utility>

Passenger::Passenger(std::string name, int age, std::string gender, std::string phone)
    : name_(std::move(name)), age_(age), gender_(std::move(gender)), phone_(std::move(phone)) {
    if (name_.empty() || age_ < 1 || age_ > 120 || phone_.empty())
        throw RailwayException("Invalid passenger details.");
}
const std::string& Passenger::getName() const { return name_; }
int Passenger::getAge() const { return age_; }
const std::string& Passenger::getGender() const { return gender_; }
const std::string& Passenger::getPhone() const { return phone_; }
