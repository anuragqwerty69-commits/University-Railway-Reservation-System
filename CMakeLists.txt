cmake_minimum_required(VERSION 3.16)
project(UniversityRailwayReservationSystem LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
add_executable(railway_reservation
    src/main.cpp src/Train.cpp src/Passenger.cpp src/Booking.cpp src/RailwaySystem.cpp)
target_include_directories(railway_reservation PRIVATE include)
