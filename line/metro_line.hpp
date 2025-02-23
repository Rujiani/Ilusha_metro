#ifndef METRO_LINE_HPP_
#define METRO_LINE_HPP_

#include <ostream>
#include <memory>
#include <unordered_set>
#include <string>
#include "../Stations/station.hpp"

template<class T>
using Table = std::unordered_set<T>;

using std::shared_ptr;
using std::string;

namespace mgm {

/**
 * @brief Represents a metro line consisting of stations.
 */
class Line {
    string name;
    Table<shared_ptr<station>> stations_table;
public:
    /**
     * @brief Default constructor.
     */
    Line() noexcept : name{} {}

    /**
     * @brief Constructs a line with the given name.
     * @param n The name of the line.
     */
    Line(string n) : name(std::move(n)) {}

    /**
     * @brief Gets the name of the line.
     * @return The line name.
     */
    string getName() const { return name; }

    /**
     * @brief Adds a station to the line.
     * @param st The station to add.
     */
    void addElement(station &&st);

    /**
     * @brief Finds a station on the line by name.
     * @param name The name of the station to find.
     * @return A shared pointer to the station.
     * @throws std::invalid_argument if the station is not found.
     */
    shared_ptr<station> find(const string &name) const;

    /**
     * @brief Removes a station from the line by its name.
     * @param stationName The name of the station to remove.
     * @throws std::invalid_argument if the station is not found.
     */
    void removeElement(const string &stationName);

    /**
     * @brief Returns a string representation of all stations on the line.
     * @return A string containing all station names and their types.
     */
    string getTableStr() const;

    /**
     * @brief Displays the station table to an output stream.
     * @param ost The output stream.
     * @return The output stream.
     */
    std::ostream &showTable(std::ostream &ost) const;

    bool operator==(const Line &other) const noexcept { return name == other.name; }
    bool operator!=(const Line &other) const noexcept { return name != other.name; }
    bool operator>(const Line &other) const noexcept { return name > other.name; }
    bool operator>=(const Line &other) const noexcept { return name >= other.name; }
    bool operator<(const Line &other) const noexcept { return name < other.name; }
    bool operator<=(const Line &other) const noexcept { return name <= other.name; }

    /**
     * @brief Provides access to the underlying station table.
     * @return A constant reference to the station table.
     */
    const Table<shared_ptr<station>> &getStations() const { return stations_table; }
};

} // namespace mgm

#endif
