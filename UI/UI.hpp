#ifndef UI_HPP_
#define UI_HPP_

#include "../Metro_system/metro_system.hpp"

namespace mgm {

/**
 * @brief UI class implementing the MVC Controller and View.
 *
 * This class provides a dialog interface for interacting with the MetroSystem.
 * It holds only a reference to the MetroSystem object.
 */
class UI {
public:
    /**
     * @brief Constructs the UI with a reference to the MetroSystem.
     * @param system Reference to a MetroSystem object.
     */
    UI(MetroSystem &system);

    /**
     * @brief Starts the UI update loop.
     */
    void update();

private:
    MetroSystem &metroSystem;

    /**
     * @brief Prints the main menu.
     */
    void printMenu() const;

    /**
     * @brief Handles a single command input.
     * @param choice The user's command choice.
     */
    void handleCommand(int choice);
};

} // namespace mgm

#endif // UI_HPP_
