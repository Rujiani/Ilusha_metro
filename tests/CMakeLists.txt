find_package(GTest REQUIRED)

add_executable(test test.cpp)

target_link_libraries(test PRIVATE GTest::GTest GTest::Main gcov LookUpTable)
target_compile_options(test PRIVATE --coverage -Wextra -Wall)