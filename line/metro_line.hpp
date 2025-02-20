#ifndef METRO_LINE_HPP_
#define METRO_LINE_HPP_
#include <ostream>
#include <memory>
#include <unordered_set>
#include "../Stations/station.hpp"

template<class T>
using Table = std::unordered_set<T>;

using std::shared_ptr;

namespace mgm {

class Line{
    string name;
    Table<std::shared_ptr<station>> stations_table;
    public:

    Line()noexcept:name{}{}

    Line(string n):name(std::move(n)){}

    string getName() const{return name;}

    void addElement(station &&st);

    shared_ptr<station> find(const string &name)const;

    string getTableStr()const;

    std::ostream &showTable(std::ostream &ost)const;

    bool operator == (const Line &other)const noexcept{return name == other.name;}
    bool operator!=(const Line &other) const noexcept { return name != other.name; }
    bool operator>(const Line &other) const noexcept { return name > other.name; }
    bool operator>=(const Line &other) const noexcept { return name >= other.name; }
    bool operator<(const Line &other) const noexcept { return name < other.name; }
    bool operator<=(const Line &other) const noexcept { return name <= other.name; }
};

}

#endif