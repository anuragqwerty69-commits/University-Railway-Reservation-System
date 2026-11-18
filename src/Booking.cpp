#include "Booking.h"
#include <iostream>
#include <utility>

Booking::Booking(long long pnr, int trainNumber, std::string journeyDate,
                 Passenger passenger, BookingStatus status, int seatNumber)
    : pnr_(pnr), trainNumber_(trainNumber), journeyDate_(std::move(journeyDate)),
      passenger_(std::move(passenger)), status_(status), seatNumber_(seatNumber) {}
long long Booking::getPnr() const { return pnr_; }
int Booking::getTrainNumber() const { return trainNumber_; }
const std::string& Booking::getJourneyDate() const { return journeyDate_; }
const Passenger& Booking::getPassenger() const { return passenger_; }
BookingStatus Booking::getStatus() const { return status_; }
int Booking::getSeatNumber() const { return seatNumber_; }
void Booking::confirm(int seatNumber) { status_ = BookingStatus::Confirmed; seatNumber_ = seatNumber; }
void Booking::cancel() { status_ = BookingStatus::Cancelled; seatNumber_ = 0; }
std::string Booking::statusText(BookingStatus status) {
    switch (status) {
        case BookingStatus::Confirmed: return "CONFIRMED";
        case BookingStatus::Waitlisted: return "WAITLISTED";
        case BookingStatus::Cancelled: return "CANCELLED";
    }
    return "UNKNOWN";
}
void Booking::display() const {
    std::cout << "PNR: " << pnr_ << " | Train: " << trainNumber_
              << " | Passenger: " << passenger_.getName()
              << " | Date: " << journeyDate_ << " | Status: " << statusText(status_);
    if (status_ == BookingStatus::Confirmed) std::cout << " | Seat: " << seatNumber_;
    std::cout << '\n';
}
