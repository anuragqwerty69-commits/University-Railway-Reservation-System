#include "RailwaySystem.h"
#include "Exceptions.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cctype>

namespace {
std::string safe(const std::string& value) {
    std::string result = value;
    std::replace(result.begin(), result.end(), '|', '/');
    return result;
}
std::string prompt(const std::string& label) {
    std::cout << label;
    std::string value;
    std::getline(std::cin, value);
    return value;
}
int readInt(const std::string& label) {
    while (true) {
        std::string raw = prompt(label);
        try {
            std::size_t used = 0;
            int value = std::stoi(raw, &used);
            if (used != raw.size()) throw std::invalid_argument("extra");
            return value;
        } catch (...) { std::cout << "Enter a valid whole number.\n"; }
    }
}
std::vector<std::string> split(const std::string& line) {
    std::vector<std::string> parts;
    std::stringstream stream(line);
    std::string part;
    while (std::getline(stream, part, '|')) parts.push_back(part);
    return parts;
}
}

RailwaySystem::RailwaySystem() {
    loadData();
    if (trains_.empty()) { seedTrains(); saveData(); }
}
void RailwaySystem::seedTrains() {
    trains_.emplace(12101, Train(12101, "Deccan Express", "Pune", "Mumbai", "07:15", 3, 180.0));
    trains_.emplace(11008, Train(11008, "Deccan Queen", "Pune", "Mumbai", "17:10", 3, 220.0));
    trains_.emplace(12124, Train(12124, "Pune - Mumbai Intercity", "Pune", "Mumbai", "06:50", 3, 200.0));
    trains_.emplace(11029, Train(11029, "Koyna Express", "Mumbai", "Pune", "08:40", 3, 190.0));
    trains_.emplace(22105, Train(22105, "Indrayani Express", "Mumbai", "Pune", "18:35", 3, 210.0));
}
void RailwaySystem::loadData() {
    {
        std::ifstream file("data/trains.txt");
        std::string line;
        while (std::getline(file, line)) try {
            auto p = split(line);
            if (p.size() != 7) continue;
            int n = std::stoi(p[0]);
            trains_.emplace(n, Train(n, p[1], p[2], p[3], p[4], std::stoi(p[5]), std::stod(p[6])));
        } catch (...) {}
    }
    {
        std::ifstream file("data/bookings.txt");
        std::string line;
        while (std::getline(file, line)) try {
            auto p = split(line);
            if (p.size() != 10) continue;
            auto status = p[7] == "CONFIRMED" ? BookingStatus::Confirmed :
                          p[7] == "WAITLISTED" ? BookingStatus::Waitlisted : BookingStatus::Cancelled;
            Passenger passenger(p[3], std::stoi(p[4]), p[5], p[6]);
            Booking booking(std::stoll(p[0]), std::stoi(p[1]), p[2], passenger, status, std::stoi(p[8]));
            bookings_.push_back(booking);
            nextPnr_ = std::max(nextPnr_, booking.getPnr() + 1);
        } catch (...) {}
    }
}
void RailwaySystem::saveData() const {
    {
        std::ofstream file("data/trains.txt");
        for (const auto& [number, t] : trains_)
            file << number << '|' << safe(t.getName()) << '|' << safe(t.getSource()) << '|'
                 << safe(t.getDestination()) << '|' << t.getDeparture() << '|'
                 << t.getCapacity() << '|' << t.getFare() << '\n';
    }
    {
        std::ofstream file("data/bookings.txt");
        for (const auto& b : bookings_) {
            const auto& p = b.getPassenger();
            file << b.getPnr() << '|' << b.getTrainNumber() << '|' << b.getJourneyDate()
                 << '|' << safe(p.getName()) << '|' << p.getAge() << '|' << safe(p.getGender())
                 << '|' << safe(p.getPhone()) << '|' << Booking::statusText(b.getStatus())
                 << '|' << b.getSeatNumber() << "|-\n";
        }
    }
}
int RailwaySystem::confirmedCount(int trainNumber, const std::string& date) const {
    int count = 0;
    for (const auto& b : bookings_)
        if (b.getTrainNumber() == trainNumber && b.getJourneyDate() == date
            && b.getStatus() == BookingStatus::Confirmed) ++count;
    return count;
}
int RailwaySystem::nextAvailableSeat(int trainNumber, const std::string& date) const {
    auto train = trains_.find(trainNumber);
    if (train == trains_.end()) return 0;
    std::vector<bool> used(static_cast<std::size_t>(train->second.getCapacity()) + 1, false);
    for (const auto& b : bookings_)
        if (b.getTrainNumber() == trainNumber && b.getJourneyDate() == date
            && b.getStatus() == BookingStatus::Confirmed && b.getSeatNumber() > 0
            && b.getSeatNumber() <= train->second.getCapacity())
            used[static_cast<std::size_t>(b.getSeatNumber())] = true;
    for (int seat = 1; seat <= train->second.getCapacity(); ++seat)
        if (!used[static_cast<std::size_t>(seat)]) return seat;
    return 0;
}
void RailwaySystem::promoteWaitlisted(int trainNumber, const std::string& date) {
    auto train = trains_.find(trainNumber);
    if (train == trains_.end()) return;
    for (auto& booking : bookings_) {
        if (booking.getTrainNumber() == trainNumber && booking.getJourneyDate() == date
            && booking.getStatus() == BookingStatus::Waitlisted) {
            int seat = nextAvailableSeat(trainNumber, date);
            if (seat == 0) break;
            booking.confirm(seat);
        }
    }
}
void RailwaySystem::listTrains() const {
    std::cout << "\nTRAIN NO | NAME | ROUTE | DEPARTURE | CAPACITY | BASE FARE\n";
    for (const auto& [number, train] : trains_) train.display();
}
void RailwaySystem::searchTrains() const {
    std::string from = prompt("From station: "), to = prompt("To station: ");
    auto lower = [](std::string s) {
        std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c){ return static_cast<char>(std::tolower(c)); });
        return s;
    };
    bool found = false;
    for (const auto& [number, train] : trains_)
        if (lower(train.getSource()) == lower(from) && lower(train.getDestination()) == lower(to)) {
            train.display(); found = true;
        }
    if (!found) std::cout << "No direct train found for this route.\n";
}
void RailwaySystem::bookTicket() {
    int trainNo = readInt("Enter train number: ");
    auto train = trains_.find(trainNo);
    if (train == trains_.end()) throw RailwayException("Train number does not exist.");
    std::string date = prompt("Journey date (YYYY-MM-DD): ");
    if (date.size() != 10 || date[4] != '-' || date[7] != '-')
        throw RailwayException("Use date format YYYY-MM-DD.");
    std::string name = prompt("Passenger name: ");
    int age = readInt("Passenger age: ");
    std::string gender = prompt("Gender: ");
    std::string phone = prompt("Phone number: ");
    Passenger passenger(name, age, gender, phone);
    BookingStatus status;
    int seat = nextAvailableSeat(trainNo, date);
    if (seat != 0) status = BookingStatus::Confirmed;
    else status = BookingStatus::Waitlisted;
    Booking booking(nextPnr_++, trainNo, date, passenger, status, seat);
    bookings_.push_back(booking);
    saveData();
    std::cout << "\nBooking created successfully.\n";
    booking.display();
    std::cout << "Base fare: Rs. " << std::fixed << std::setprecision(2) << train->second.getFare() << '\n';
}
void RailwaySystem::cancelTicket() {
    long long pnr;
    while (true) {
        std::string raw = prompt("Enter PNR to cancel: ");
        try { std::size_t used=0; pnr=std::stoll(raw,&used); if (used != raw.size()) throw std::invalid_argument("extra"); break; }
        catch (...) { std::cout << "Enter a valid PNR.\n"; }
    }
    auto it = std::find_if(bookings_.begin(), bookings_.end(),
                           [&](const Booking& b){ return b.getPnr() == pnr; });
    if (it == bookings_.end() || it->getStatus() == BookingStatus::Cancelled)
        throw RailwayException("Active booking not found for this PNR.");
    int trainNo = it->getTrainNumber();
    std::string date = it->getJourneyDate();
    it->cancel();
    promoteWaitlisted(trainNo, date);
    saveData();
    std::cout << "Ticket cancelled. Any available seat has been assigned to the earliest waitlisted passenger.\n";
}
void RailwaySystem::checkPnr() const {
    std::string raw = prompt("Enter PNR: ");
    long long pnr = 0;
    try { std::size_t used=0; pnr=std::stoll(raw,&used); if (used != raw.size()) throw std::invalid_argument("extra"); }
    catch (...) { throw RailwayException("Invalid PNR format."); }
    auto it = std::find_if(bookings_.begin(), bookings_.end(),
                           [&](const Booking& b){ return b.getPnr() == pnr; });
    if (it == bookings_.end()) throw RailwayException("PNR not found.");
    it->display();
}
void RailwaySystem::listBookings() const {
    if (bookings_.empty()) { std::cout << "No bookings recorded.\n"; return; }
    for (const auto& booking : bookings_) booking.display();
}
void RailwaySystem::showAvailability() const {
    int trainNo = readInt("Enter train number: ");
    auto it = trains_.find(trainNo);
    if (it == trains_.end()) throw RailwayException("Train not found.");
    std::string date = prompt("Journey date (YYYY-MM-DD): ");
    int confirmed = confirmedCount(trainNo, date);
    int available = it->second.getCapacity() - confirmed;
    int waiting = 0;
    for (const auto& b : bookings_)
        if (b.getTrainNumber() == trainNo && b.getJourneyDate() == date
            && b.getStatus() == BookingStatus::Waitlisted) ++waiting;
    std::cout << "Train: " << it->second.getName() << " | Date: " << date
              << " | Available seats: " << available << " | Waitlist: " << waiting << '\n';
}
