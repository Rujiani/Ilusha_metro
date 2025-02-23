#ifndef STATION_HPP_
#define STATION_HPP_

#include <string>
using std::string;

/**
 * @file station.hpp
 * @brief Contains the definition of the station class for the metro system.
 */

namespace mgm {

/**
 * @brief Forward declaration of the station class.
 */
class station;

/**
 * @brief Concept that checks if a type is derived from station.
 *
 * This concept ensures that the type T is a subclass of station.
 */
template<typename T>
concept DerivedFromStation = std::is_base_of_v<station, T>;

/**
 * @brief Represents a metro station.
 *
 * The station class encapsulates the basic properties of a metro station,
 * including its name and type.
 */
class station {
private:
    string name; /**< The name of the station. */
    string type; /**< The type of the station (e.g., "Direct", "transition"). */
public:
    /**
     * @brief Constructs a station with an optional name and type.
     *
     * @param n The name of the station. Defaults to an empty string.
     * @param tp The type of the station. Defaults to "Direct".
     */
    station(string n = "", string tp = "Direct") noexcept : name(n), type(tp) {}

    /**
     * @brief Gets a reference to the station's name.
     *
     * @return A non-const reference to the station's name.
     */
    string& getName() noexcept { return name; }
    
    /**
     * @brief Gets a constant reference to the station's name.
     *
     * @return A const reference to the station's name.
     */
    const string& getName() const noexcept { return name; }
    
    /**
     * @brief Sets the station's name.
     *
     * @param new_name The new name for the station.
     */
    void setName(const string &new_name) { name = new_name; }

    /**
     * @brief Gets a constant reference to the station's type.
     *
     * @return A const reference to the station's type.
     */
    const string& getType() const { return type; }
    
    /**
     * @brief Gets the station's type.
     *
     * @return The station's type as a string.
     */
    string getType() { return type; }
    
    /**
     * @brief Converts this station to another station type.
     *
     * This template function allows converting a station object to a derived station type.
     *
     * @tparam T The target station type, which must be derived from station.
     * @return A new object of type T constructed with the station's name.
     */
    template<DerivedFromStation T>
    T convert_station() { return T(name); }
    
    /**
     * @brief Virtual destructor.
     */
    virtual ~station() = default;
};

} // namespace mgm

#endif
