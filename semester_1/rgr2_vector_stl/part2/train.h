#pragma once

#include <string>
#include <iostream>
#include "time_utility.h"

using TrainId = size_t;
using namespace time_utility;

enum class TrainType { 
    PASSENGER, FREIGHT, HIGH_SPEED, SUBWAY, SPECIALIZED 
};

class Train {
private:
    TrainId id_;
    TrainType type_;
    std::string destination_;
    std::time_t dispatch_time_;
    std::time_t travelling_time_;

public:
    Train()
        : id_(0), type_(TrainType::PASSENGER), destination_(""), dispatch_time_(0), travelling_time_(0) {
    }

    Train(size_t id, TrainType type, const std::string& destination, std::time_t dispatch_time,
          std::time_t travelling_time)
        : id_(id), type_(type), destination_(destination), dispatch_time_(dispatch_time), travelling_time_(travelling_time) {
    }

    size_t GetId() const {
        return id_;
    }
    TrainType GetType() const {
        return type_;
    }
    std::string GetDestination() const {
        return destination_;
    }
    std::time_t GetDispatchTime() const {
        return dispatch_time_;
    }
    std::time_t GetTravellingTime() const {
        return travelling_time_;
    }

    void Print() const {
        std::cout << "Train #" << id_ << " |Type: " << TrainTypeToString(type_) << " |Destination: " << destination_ << " |Dispatch time: ";
        time_utility::PrintTime(dispatch_time_);
        std::cout << " |Travelling time(mins): " << travelling_time_ / 60 << "\n";
    }

    static std::string TrainTypeToString(TrainType type) {
        switch (type) {
            case TrainType::PASSENGER:
                return "Passenger";
            case TrainType::FREIGHT:
                return "Freight";
            case TrainType::HIGH_SPEED:
                return "High_speed";
            case TrainType::SUBWAY:
                return "Subway";
            case TrainType::SPECIALIZED:
                return "Specialized";
            default:
                return "Unknown";
        }
    }

    static Train FromString(const std::string& line) {
        size_t pos = 0, next = 0;

        next = line.find(';', pos);
        size_t id = std::stoul(line.substr(pos, next - pos));
        pos = next + 1;

        next = line.find(';', pos);
        int type_int = std::stoi(line.substr(pos, next - pos));
        pos = next + 1;

        next = line.find(';', pos);
        std::string destination = line.substr(pos, next - pos);
        pos = next + 1;

        next = line.find(';', pos);
        std::string time_str = line.substr(pos, next - pos);
        pos = next + 1;

        size_t duration = std::stoul(line.substr(pos));

        size_t hours = std::stoul(time_str.substr(0, 2));
        size_t minutes = std::stoul(time_str.substr(3, 2));
        std::time_t dispatch = time_utility::SetTime(hours, minutes);

        TrainType type = static_cast<TrainType>(type_int);
        return Train(id, type, destination, dispatch, duration * 60);
    }
};
