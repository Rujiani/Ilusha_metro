find_package(GTest REQUIRED)

add_executable(test test.cpp ../Metro_system/metro_system.cpp ../line/metro_line.cpp)

target_link_libraries(test PRIVATE GTest::GTest GTest::Main gcov LookUpTable MetroSystem Station TransitionalSt MetroLine)
target_compile_options(test PRIVATE --coverage -Wextra -Wall)