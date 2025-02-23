#include "UI.hpp"
#include <iostream>
#include <limits>
#include "../Stations/station.hpp"

using namespace mgm;
using std::cout;
using std::cin;
using std::string;

UI::UI(MetroSystem &system) : metroSystem(system) {}

void UI::printMenu() const {
    cout << "\n=== Metro System Menu ===\n";
    cout << "1. Add Line\n";
    cout << "2. Remove Line\n";
    cout << "3. Add Station to Line\n";
    cout << "4. Remove Station from Line\n";
    cout << "5. Modify Station in Line\n";
    cout << "6. Find Station on Line\n";
    cout << "7. Find Transition Station by Name\n";
    cout << "8. Validate System\n";
    cout << "9. Show System Description\n";
    cout << "0. Exit\n";
    cout << "Enter your choice: ";
}

void UI::handleCommand(int choice) {
    string lineName, stationName, newName, newType;
    try {
        switch(choice) {
            case 1:
                cout << "Enter line name to add: ";
                cin >> lineName;
                metroSystem.addLine(lineName);
                cout << "Line added.\n";
                break;
            case 2:
                cout << "Enter line name to remove: ";
                cin >> lineName;
                metroSystem.removeLine(lineName);
                cout << "Line removed.\n";
                break;
            case 3:
                cout << "Enter line name: ";
                cin >> lineName;
                cout << "Enter station name: ";
                cin >> stationName;
                cout << "Enter station type (Direct/transition): ";
                cin >> newType;
                metroSystem.addStationToLine(lineName, station(stationName, newType));
                cout << "Station added to line.\n";
                break;
            case 4:
                cout << "Enter line name: ";
                cin >> lineName;
                cout << "Enter station name to remove: ";
                cin >> stationName;
                metroSystem.removeStationFromLine(lineName, stationName);
                cout << "Station removed from line.\n";
                break;
            case 5:
                cout << "Enter line name: ";
                cin >> lineName;
                cout << "Enter station name to modify: ";
                cin >> stationName;
                cout << "Enter new station name: ";
                cin >> newName;
                cout << "Enter new station type (Direct/transition): ";
                cin >> newType;
                metroSystem.modifyStationInLine(lineName, stationName, newName, newType);
                cout << "Station modified.\n";
                break;
            case 6: {
                cout << "Enter line name: ";
                cin >> lineName;
                cout << "Enter station name to find: ";
                cin >> stationName;
                auto st = metroSystem.findStationOnLine(lineName, stationName);
                cout << "Found station: " << st->getName() << ", Type: " << st->getType() << "\n";
                break;
            }
            case 7: {
                cout << "Enter transition station name to find: ";
                cin >> stationName;
                auto st = metroSystem.findTransitionStationByName(stationName);
                cout << "Found transition station: " << st->getName() << "\n";
                break;
            }
            case 8:
                metroSystem.validateSystem();
                cout << "System validated.\n";
                break;
            case 9:
                cout << metroSystem.getSystemDescription() << "\n";
                break;
            case 0:
                cout << "Exiting.\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
                break;
        }
    } catch (std::exception &ex) {
        cout << "Error: " << ex.what() << "\n";
    }
}

void UI::update() {
    int choice = -1;
    while (true) {
        printMenu();
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (choice == 0) {
            std::cout << "Exiting.\n";
            break;
        }
        handleCommand(choice);
    }
}
