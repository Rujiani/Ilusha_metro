#ifndef METRO_LINE_HPP_
#define METRO_LINE_HPP_

#include <ostream>
#include <memory>
#include <string>
#include "../Stations/station.hpp"
#include "../container/lookUpTable.hpp"

using std::shared_ptr;
using std::string;

namespace mgm {

/**
 * @brief Represents a metro line consisting of stations.
 *
 * This class stores stations in a LookupTable mapping station names to shared pointers to stations.
 */
class Line {
    string name;
    mgc::LookupTable<string, shared_ptr<station>> stations_table;
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
     * @brief Adds a station to the line while preserving its dynamic type.
     * @tparam T The type of the station to add. Must be derived from station.
     * @param st The station object to add.
     * @throws std::invalid_argument if a station with the same name already exists.
     */
    template<typename T>
    requires std::is_base_of_v<station, std::decay_t<T>>
    void addElement(T &&st) {
        string key = st.getName();
        if (stations_table.find(key) != stations_table.size())
            throw std::invalid_argument("Error: Station already exists on this line.");
        auto ptr = std::make_shared<std::decay_t<T>>(std::forward<T>(st));
        stations_table.insert(key, ptr);
    }

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

    /**
     * @brief Provides access to the underlying station table.
     * @return A constant reference to the LookupTable.
     */
    const mgc::LookupTable<string, shared_ptr<station>> &getStations() const { return stations_table; }
};

} // namespace mgm

#endif
