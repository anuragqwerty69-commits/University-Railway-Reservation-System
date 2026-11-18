#pragma once
#include "Booking.h"
#include "Train.h"
#include <map>
#include <vector>
#include <string>

class RailwaySystem {
    std::map<int, Train> trains_;
    std::vector<Booking> bookings_;
    long long nextPnr_{2600000001LL};

    void loadData();
    void saveData() const;
    void seedTrains();
    int confirmedCount(int trainNumber, const std::string& date) const;
    int nextAvailableSeat(int trainNumber, const std::string& date) const;
    void promoteWaitlisted(int trainNumber, const std::string& date);
public:
    RailwaySystem();
    void listTrains() const;
    void searchTrains() const;
    void bookTicket();
    void cancelTicket();
    void checkPnr() const;
    void listBookings() const;
    void showAvailability() const;
};
