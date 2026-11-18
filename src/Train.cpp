#include "Train.h"
#include "Exceptions.h"
#include <iostream>
#include <utility>

Train::Train(int number, std::string name, std::string source, std::string destination,
             std::string departure, int capacity, double fare)
    : number_(number), name_(std::move(name)), source_(std::move(source)),
      destination_(std::move(destination)), departure_(std::move(departure)),
      capacity_(capacity), fare_(fare) {
    if (number_ <= 0 || name_.empty() || source_.empty() || destination_.empty()
        || capacity_ <= 0 || fare_ < 0)
        throw RailwayException("Invalid train details.");
}
int Train::getNumber() const { return number_; }
const std::string& Train::getName() const { return name_; }
const std::string& Train::getSource() const { return source_; }
const std::string& Train::getDestination() const { return destination_; }
const std::string& Train::getDeparture() const { return departure_; }
int Train::getCapacity() const { return capacity_; }
double Train::getFare() const { return fare_; }
void Train::display() const {
    std::cout << number_ << " | " << name_ << " | " << source_ << " -> " << destination_
              << " | " << departure_ << " | Seats: " << capacity_
              << " | Fare: Rs. " << fare_ << '\n';
}
