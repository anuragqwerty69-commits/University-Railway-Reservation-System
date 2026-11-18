#pragma once
#include <stdexcept>
#include <string>

class RailwayException : public std::runtime_error {
public:
    explicit RailwayException(const std::string& message) : std::runtime_error(message) {}
};
