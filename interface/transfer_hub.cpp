#include "transfer_hub.hpp"
#include <algorithm>
#include <stdexcept>

namespace mgm {

void transfer_hub::add_station(string name_of_station, string name_of_line){
    if(station_name_line.size() >= 3)
        throw std::invalid_argument("Error: The capacity of the transfer_hub cannot exceed 3.");
    station_name_line.emplace_back(std::make_pair(name_of_station, name_of_line));
}

string transfer_hub::get_station_names()const{
    string result;
    std::for_each(station_name_line.begin(), station_name_line.end(), 
        [&result](auto &i){result += i.first + '\n';});
    return result;
}

string transfer_hub::get_lines_names()const{
    string result;
    std::for_each(station_name_line.begin(), station_name_line.end(), 
        [&result](auto &i){result += i.second + '\n';});
    return result;        
}

string transfer_hub::get_stations_lines_names()const{
    string result;
    std::for_each(station_name_line.begin(), station_name_line.end(), 
        [&result](auto &i){result += i.first + '-' + i.second + '\n';});
    return result;        
}
}