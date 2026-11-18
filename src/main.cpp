#include "RailwaySystem.h"
#include "Exceptions.h"
#include <iostream>
#include <limits>

void menu() {
    std::cout << "\n============== RAILWAY RESERVATION SYSTEM ==============\n"
              << " 1. View all trains       2. Search trains by route\n"
              << " 3. Book ticket           4. Cancel ticket\n"
              << " 5. Check PNR status      6. View all bookings\n"
              << " 7. Check seat availability\n"
              << " 0. Exit\n"
              << "=========================================================\n";
}
int main() {
    try {
        RailwaySystem system;
        std::cout << "Welcome to the Railway Reservation System (C++17)\n";
        while (true) {
            menu();
            std::cout << "Enter choice: ";
            int choice;
            if (!(std::cin >> choice)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Please enter a numeric menu option.\n";
                continue;
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            try {
                switch (choice) {
                    case 1: system.listTrains(); break;
                    case 2: system.searchTrains(); break;
                    case 3: system.bookTicket(); break;
                    case 4: system.cancelTicket(); break;
                    case 5: system.checkPnr(); break;
                    case 6: system.listBookings(); break;
                    case 7: system.showAvailability(); break;
                    case 0: std::cout << "Thank you for using the system.\n"; return 0;
                    default: std::cout << "Choose a valid option from 0 to 7.\n";
                }
            } catch (const RailwayException& e) {
                std::cout << "[Reservation Error] " << e.what() << '\n';
            } catch (const std::exception& e) {
                std::cout << "[System Error] " << e.what() << '\n';
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Fatal startup error: " << e.what() << '\n';
        return 1;
    }
}
