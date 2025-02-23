#include "Metro_system/metro_system.hpp"
#include "UI/UI.hpp"

int main() {
    mgm::MetroSystem metroSystem;
    mgm::UI ui(metroSystem);
    ui.update();
    return 0;
}
