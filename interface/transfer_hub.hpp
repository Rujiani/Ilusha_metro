#ifndef TRANSFER_HUB_HPP_
#define TRANSFER_HUB_HPP_

#include <list>
#include <string>
#include <utility>
using std::string;

namespace mgm {

/**
 * @brief Represents a transfer hub within the metro system.
 *
 * The transfer_hub class manages connections between stations and lines.
 * It allows adding stations with their corresponding line names and retrieving
 * lists of station names, line names, and combined station-line information.
 */
class transfer_hub {
    std::list<std::pair<string, string>> station_name_line; ///< List of pairs (station name, line name)
public:
    /**
     * @brief Default constructor.
     */
    transfer_hub() noexcept {}

    /**
     * @brief Adds a station to the transfer hub.
     *
     * @param name_of_station The name of the station.
     * @param name_of_line The name of the line.
     */
    void add_station(string name_of_station, string name_of_line);

    /**
     * @brief Retrieves the station names.
     *
     * @return A string containing all station names, each separated by a newline.
     */
    string get_station_names() const;

    /**
     * @brief Retrieves a constant reference to the list of station-line pairs.
     *
     * @return A constant reference to the internal list of station-line pairs.
     */
    const std::list<std::pair<string, string>>& get_station_list() const;

    /**
     * @brief Retrieves a modifiable reference to the list of station-line pairs.
     *
     * @return A reference to the internal list of station-line pairs.
     */
    std::list<std::pair<string, string>>& get_station_list();

    /**
     * @brief Retrieves the line names.
     *
     * @return A string containing all line names, each separated by a newline.
     */
    string get_lines_names() const;

    /**
     * @brief Retrieves combined station and line information.
     *
     * @return A string where each line contains a station name and its corresponding
     *         line name in the format "station-line", separated by newlines.
     */
    string get_stations_lines_names() const;
};

} // namespace mgm

#endif
