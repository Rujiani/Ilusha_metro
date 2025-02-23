// metro_system.cpp
#include "metro_system.hpp"
#include "../Stations/transitionstation.hpp"
#include <stdexcept>
namespace mgm {

void MetroSystem::addLine(const string &lineName) {
    if (lines.find(lineName) != lines.end())
        throw std::invalid_argument("Error: A line with this name already exists.");
    lines.emplace(lineName, Line(lineName));
}

void MetroSystem::removeLine(const string &lineName) {
    auto it = lines.find(lineName);
    if (it == lines.end())
        throw std::invalid_argument("Error: Line not found.");
    lines.erase(it);
}

void MetroSystem::addStationToLine(const string &lineName, station &&st) {
    auto it = lines.find(lineName);
    if (it == lines.end())
        throw std::invalid_argument("Error: Line not found.");
    it->second.addElement(std::move(st));
}

void MetroSystem::removeStationFromLine(const string &lineName, const string &stationName) {
    auto it = lines.find(lineName);
    if (it == lines.end())
        throw std::invalid_argument("Error: Line not found.");
    it->second.removeElement(stationName);
}

void MetroSystem::modifyStationInLine(const string &lineName,
                                      const string &stationName,
                                      const string &newName,
                                      const string &newType) {
    auto it = lines.find(lineName);
    if (it == lines.end())
        throw std::invalid_argument("Error: Line not found.");
    it->second.removeElement(stationName);
    if (newType == "transition") {
        transition_station ts(newName);
        it->second.addElement(std::move(ts));
    } else {
        station s(newName, newType);
        it->second.addElement(std::move(s));
    }
}

std::shared_ptr<station> MetroSystem::findStationOnLine(const string &lineName,
                                                        const string &stationName) const {
    auto it = lines.find(lineName);
    if (it == lines.end())
        throw std::invalid_argument("Error: Line not found.");
    return it->second.find(stationName);
}

std::shared_ptr<station> MetroSystem::findTransitionStationByName(const string &transitionStationName) const {
    for (const auto &linePair : lines) {
        try {
            auto st = linePair.second.find(transitionStationName);
            if (st->getType() == "transition")
                return st;
        }
        catch (...) {
            // Continue searching
        }
    }
    throw std::invalid_argument("Error: Transition station not found.");
}

void MetroSystem::validateSystem() {
    for (auto &linePair : lines) {
        Line &line = linePair.second;
        for (const auto &st_ptr : line.getStations()) {
            if (st_ptr->getType() == "transition") {
                transition_station* ts = dynamic_cast<transition_station*>(st_ptr.get());
                if (ts) {
                    auto &connections = ts->get_station_list();
                    for (auto it = connections.begin(); it != connections.end(); ) {
                        const string &targetStation = it->first;
                        const string &targetLine = it->second;
                        bool valid = false;
                        auto targetLineIt = lines.find(targetLine);
                        if (targetLineIt != lines.end()) {
                            try {
                                targetLineIt->second.find(targetStation);
                                valid = true;
                            }
                            catch (...) {
                                valid = false;
                            }
                        }
                        if (!valid)
                            it = connections.erase(it);
                        else
                            ++it;
                    }
                }
            }
        }
    }
}

std::string MetroSystem::getSystemDescription() const {
    string oss;
    for (const auto &linePair : lines) {
        oss += "Line: " + linePair.first + "\n";
        oss += linePair.second.getTableStr() + "\n";
    }
    return oss;
}

} // namespace mgm