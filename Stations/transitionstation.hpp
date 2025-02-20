#ifndef TRANSITION_STATION_HPP_
#define TRANSITION_STATION_HPP_

#include "station.hpp"
#include "../interface/transfer_hub.hpp"

namespace mgm {

class direct_station;

class transition_station: public station, public transfer_hub{
    public:
    transition_station(string name):station(name, "transition"){}
};

}

#endif