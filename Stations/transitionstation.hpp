#ifndef TRANSITION_STATION_HPP_
#define TRANSITION_STATION_HPP_

#include "station.hpp"
#include "../interface/transfer_hub.hpp"

namespace mgm {

/**
 * @brief Forward declaration of the direct_station class.
 */
class direct_station;

/**
 * @brief Represents a transition station in the metro system.
 *
 * The transition_station class inherits from both station and transfer_hub.
 * It is used for stations that serve as transfer hubs between different metro lines.
 */
class transition_station : public station, public transfer_hub {
public:
    /**
     * @brief Constructs a transition station with the specified name.
     *
     * The station is initialized with the given name and is assigned the type "transition".
     *
     * @param name The name of the transition station.
     */
    transition_station(string name) : station(name, "transition") {}
};

} // namespace mgm

#endif // TRANSITION_STATION_HPP_
