#include "metro_line.hpp"
#include <utility>
#include <stdexcept>
#include <algorithm>

namespace mgm {

void Line::addElement(station &&st){
    auto res = 
        stations_table.emplace(std::make_shared<station>(std::forward<station>(st)));
    
    if(!res.second)
        throw std::invalid_argument("Error: Such line is already exist");
}

shared_ptr<station> Line::find(const string &name)const{
    auto pos = std::find_if(stations_table.begin(), stations_table.end(), [&name](auto &i){
        if(i->getName() == name)
            return true;
        return false;
    });
    if(pos == stations_table.end())
        throw std::invalid_argument("Error: No such station");
    return *pos;
}

string Line::getTableStr()const{
    string res;
    for(const auto &i : stations_table){
        res += i->getName() + '-' + i->getType() + '\n';
    }
    return res;
}

std::ostream& Line::showTable(std::ostream &ost)const{
    ost << getTableStr();
    return ost;
}

}