# University Railway Reservation System

A modular console-based railway ticket reservation application written in **C++17** for a university mini project.

## Main features
- View available trains and their route, departure time, capacity and fare
- Search trains using source and destination stations
- Book tickets with unique PNR generation
- Automatic seat allocation for each train and journey date
- Waitlist when all seats are occupied
- Cancel a booking and automatically promote the earliest waitlisted booking
- PNR status lookup and booking history
- Seat availability and waitlist count
- Persistent file storage using text files

## C++ concepts demonstrated
- Classes and objects: `Train`, `Passenger`, `Booking`, `RailwaySystem`
- Encapsulation: private data members and public methods
- Composition: `Booking` contains a `Passenger`
- Enumerations: booking status
- STL: `std::map`, `std::vector`, algorithms and iterators
- Exception handling: custom `RailwayException`, `try`/`catch`/`throw`
- File handling: persistent train and booking records
- Modular programming: header and implementation separation

## Folder structure
```text
RailwayReservationSystem/
├── include/
│   ├── Booking.h
│   ├── Exceptions.h
│   ├── Passenger.h
│   ├── RailwaySystem.h
│   └── Train.h
├── src/
│   ├── Booking.cpp
│   ├── Passenger.cpp
│   ├── RailwaySystem.cpp
│   ├── Train.cpp
│   └── main.cpp
├── data/
├── docs/
│   ├── TEST_CASES.md
│   └── UML.puml
├── CMakeLists.txt
└── README.md
```

## Build and run

### Windows (MinGW)
```bash
g++ -std=c++17 -Wall -Wextra -pedantic -Iinclude src/*.cpp -o railway_reservation.exe
railway_reservation.exe
```

### Linux / macOS
```bash
g++ -std=c++17 -Wall -Wextra -pedantic -Iinclude src/*.cpp -o railway_reservation
./railway_reservation
```

### CMake
```bash
cmake -S . -B build
cmake --build build
```

Run the program from the project root so that it can read and write the `data/` directory.

## First run
Five sample trains are created automatically if no train records exist. For a quick demonstration:
1. Select `1` to view trains.
2. Select `3` to book a ticket. Use train `12101` or another listed train.
3. Use the same train and date to fill the three sample seats and create a waitlisted booking.
4. Select `5` to check a PNR.
5. Select `4` to cancel a confirmed ticket; the earliest waitlisted booking is promoted.
6. Select `7` to check availability.

## Booking rules in this academic prototype
- Every train has a configured seat capacity.
- Seat availability is tracked separately for each journey date.
- PNR values are generated sequentially by the application.
- When seats are full, new bookings enter the waitlist.
- On cancellation, the earliest waitlisted booking for that train and date is promoted.
- This is a classroom prototype, not connected to Indian Railways or IRCTC.

## Data files
- `data/trains.txt`: train catalogue
- `data/bookings.txt`: passenger and booking records

The files are created automatically when the application saves data. Keep the `data/` folder beside the executable's working directory.

## Git collaboration plan
Suggested feature branches:
- `feature/train-search`
- `feature/booking-pnr`
- `feature/cancellation-waitlist`
- `feature/file-persistence`
- `docs/report-and-uml`

Example setup:
```bash
git init
git add .
git commit -m "Initial railway reservation system"
git branch -M main
git remote add origin <your-github-repository-url>
git push -u origin main
```

## Limitations and future enhancements
This is a single-user academic simulation. It does not connect to live train schedules, live seat inventory, payment gateways or official railway services. The date field checks the `YYYY-MM-DD` shape but does not validate calendar dates. Future scope includes calendar validation, admin authentication, coach/berth selection, fare classes, payment simulation, SQLite integration, unit tests and a GUI.
