#ifndef METRO_SYSTEM_HPP_
#define METRO_SYSTEM_HPP_

#include "../line/metro_line.hpp"
#include "../Stations/station.hpp"
#include <unordered_map>
#include <string>
#include <memory>

namespace mgm {

/**
 * @brief Represents the metro system, managing lines and stations.
 *
 * This class provides functionality to add, remove, and modify lines and stations,
 * as well as search for stations and validate the system configuration.
 */
class MetroSystem {
    std::unordered_map<string, Line> lines;
public:
    /**
     * @brief Default constructor.
     */
    MetroSystem() = default;
    
    /**
     * @brief Adds a new metro line.
     * @param lineName The name of the metro line to add.
     * @throws std::invalid_argument if a line with the same name already exists.
     */
    void addLine(const string &lineName);

    /**
     * @brief Removes a metro line.
     * @param lineName The name of the metro line to remove.
     * @throws std::invalid_argument if the line is not found.
     */
    void removeLine(const string &lineName);
    
    /**
     * @brief Adds a station to a specified line.
     * @param lineName The name of the metro line.
     * @param st The station to add.
     * @throws std::invalid_argument if the line is not found.
     */
    void addStationToLine(const string &lineName, station &&st);
    
    /**
     * @brief Removes a station from a specified line.
     * @param lineName The name of the metro line.
     * @param stationName The name of the station to remove.
     * @throws std::invalid_argument if the line is not found.
     */
    void removeStationFromLine(const string &lineName, const string &stationName);
    
    /**
     * @brief Modifies a station in a specified line.
     * @param lineName The name of the metro line.
     * @param stationName The name of the station to modify.
     * @param newName The new name for the station.
     * @param newType The new type for the station.
     * @throws std::invalid_argument if the line is not found.
     */
    void modifyStationInLine(const string &lineName,
                             const string &stationName,
                             const string &newName,
                             const string &newType);
    
    /**
     * @brief Finds a station by name on a specified line.
     * @param lineName The name of the metro line.
     * @param stationName The name of the station.
     * @return A shared pointer to the station.
     * @throws std::invalid_argument if the line or station is not found.
     */
    std::shared_ptr<station> findStationOnLine(const string &lineName,
                                               const string &stationName) const;
    /**
     * @brief Finds a transition station by name across all lines.
     * @param transitionStationName The name of the transition station.
     * @return A shared pointer to the transition station.
     * @throws std::invalid_argument if the transition station is not found.
     */
    std::shared_ptr<station> findTransitionStationByName(const string &transitionStationName) const;
    
    /**
     * @brief Validates the metro system configuration.
     *
     * For each transition station, checks all connections and removes those that refer
     * to non-existent lines or stations.
     */
    void validateSystem();
    
    /**
     * @brief Gets a string description of the entire metro system.
     * @return A string containing the description of all lines and their stations.
     */
    std::string getSystemDescription() const;
};

} // namespace mgm

#endif
