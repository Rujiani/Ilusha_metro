#include "metro_line.hpp"
#include <stdexcept>

namespace mgm {

shared_ptr<station> Line::find(const string &name) const {
    size_t index = stations_table.find(name);
    if (index == stations_table.size())
        throw std::invalid_argument("Error: Station not found on this line.");
    return stations_table[index].second;
}

void Line::removeElement(const string &stationName) {
    if (!stations_table.erase(stationName))
        throw std::invalid_argument("Error: Station not found in line.");
}

string Line::getTableStr() const {
    string res;
    for (auto it = stations_table.begin(); it != stations_table.end(); ++it) {
        res += it->second->getName() + '-' + it->second->getType() + '\n';
    }
    return res;
}

std::ostream &Line::showTable(std::ostream &ost) const {
    ost << getTableStr();
    return ost;
}

} // namespace mgm
