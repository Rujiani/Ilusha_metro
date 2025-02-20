#ifndef TRANSFER_HUB_HPP_
#define TRANSFER_HUB_HPP_

#include <list>
#include <string>
#include <utility>
using std::string;

namespace mgm {
class transfer_hub{
    std::list<std::pair<string, string>> station_name_line;
    public:transfer_hub()noexcept{}

    void add_station(string name_of_station, string name_of_line);

    string get_station_names()const;

    string get_lines_names()const;

    string get_stations_lines_names()const;
};

}

#endif