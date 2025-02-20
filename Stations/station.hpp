#ifndef STATION_HPP_
#define STATION_HPP_

#include <string>
using std::string;

//my great metro
namespace mgm {

class station;

template<typename T>
concept DerivedFromStation = std::is_base_of_v<station, T>;

class station{
    private:
    string name, type;
    public:

    station(string n = "", string tp = "Direct")noexcept:name(n), type(tp){}

    string& getName()noexcept{return name;}
    const string& getName()const noexcept{return name;}
    void setName(const string &new_name){name = new_name;}

    const string& getType()const{return type;}
    string getType(){return type;}
    template<DerivedFromStation T>
    T convert_station(){return T(name);}
};

}

#endif