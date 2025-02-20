add_library(Station INTERFACE station.hpp)
add_library(TransitionalSt INTERFACE transitionstation.hpp)

target_link_libraries(TransitionalSt INTERFACE Station TransferHub)