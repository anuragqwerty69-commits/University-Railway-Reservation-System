#pragma once
#include "Passenger.h"
#include <string>

enum class BookingStatus { Confirmed, Waitlisted, Cancelled };

class Booking {
    long long pnr_;
    int trainNumber_;
    std::string journeyDate_;
    Passenger passenger_;
    BookingStatus status_;
    int seatNumber_; // 0 means no confirmed seat
public:
    Booking(long long pnr, int trainNumber, std::string journeyDate,
            Passenger passenger, BookingStatus status, int seatNumber);
    long long getPnr() const;
    int getTrainNumber() const;
    const std::string& getJourneyDate() const;
    const Passenger& getPassenger() const;
    BookingStatus getStatus() const;
    int getSeatNumber() const;
    void confirm(int seatNumber);
    void cancel();
    static std::string statusText(BookingStatus status);
    void display() const;
};
