#include "metro_system.hpp"
#include "../Stations/transitionstation.hpp"
#include <stdexcept>
#include <algorithm>
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
        }
    }
    throw std::invalid_argument("Error: Transition station not found.");
}

void MetroSystem::validateSystem() {
    std::for_each(lines.begin(), lines.end(), [this](auto &linePair) {
        Line &line = linePair.second;
        std::for_each(line.getStations().begin(), line.getStations().end(), [this](const auto &stationPair) {
            if (stationPair.second->getType() == "transition") {
                transition_station* ts = dynamic_cast<transition_station*>(stationPair.second.get());
                if (ts) {
                    auto &connections = ts->get_station_list();
                    auto new_end = std::remove_if(connections.begin(), connections.end(),
                        [this](const std::pair<string, string>& conn) -> bool {
                            const string &targetStation = conn.first;
                            const string &targetLine = conn.second;
                            auto targetLineIt = lines.find(targetLine);
                            if (targetLineIt == lines.end())
                                return true;
                            try {
                                targetLineIt->second.find(targetStation);
                                return false;
                            } catch (...) {
                                return true;
                            }
                        });
                    connections.erase(new_end, connections.end());
                }
            }
        });
    });
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
