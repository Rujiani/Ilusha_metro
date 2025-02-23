#include "metro_line.hpp"
#include <stdexcept>
#include <algorithm>
namespace mgm {

shared_ptr<station> Line::find(const string &name) const {
    auto it = std::find_if(stations_table.begin(), stations_table.end(),
                           [&name](const shared_ptr<station> &st) {
                               return st->getName() == name;
                           });
    if (it == stations_table.end())
        throw std::invalid_argument("Error: Station not found on this line.");
    return *it;
}

void Line::removeElement(const string &stationName) {
    auto it = std::find_if(stations_table.begin(), stations_table.end(),
                           [&stationName](const shared_ptr<station>& st) {
                               return st->getName() == stationName;
                           });
    if (it != stations_table.end()) {
        stations_table.erase(it);
    } else {
        throw std::invalid_argument("Error: Station not found in line.");
    }
}

string Line::getTableStr() const {
    string res;
    for (const auto &st : stations_table) {
        res += st->getName() + '-' + st->getType() + '\n';
    }
    return res;
}

std::ostream &Line::showTable(std::ostream &ost) const {
    ost << getTableStr();
    return ost;
}

} // namespace mgm
