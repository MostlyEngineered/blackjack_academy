cmake_minimum_required(VERSION 3.11.3)
project(blackjack_academy)

set(CMAKE_CXX_STANDARD 17)
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})


# Add project executable
add_executable(blackjack_academy src/main.cpp src/card_classes.cpp src/game_classes.cpp)

# Add the unit test executable
add_executable(test test/utest.cpp src/card_classes.cpp src/game_classes.cpp)

target_link_libraries(test 
    ${GTEST_LIBRARIES}
    pthread
)