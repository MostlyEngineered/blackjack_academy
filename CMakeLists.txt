cmake_minimum_required(VERSION 3.11.3)
project(blackjack_academy)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

# Add Boost for logging
ADD_DEFINITIONS(-DBOOST_LOG_DYN_LINK)
find_package(Boost COMPONENTS program_options log log_setup REQUIRED)
set(PROJECT_LIB ${PROJECT_LIB} ${Boost_LOG_LIBRARY} ${Boost_LOG_SETUP_LIBRARY})
# target_link_libraries(${PROJECT_NAME} -Wl,--start-group  ${PROJECT_LIB} -Wl,--end-group)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -fPIC -fopenmp  -DBOOST_LOG_DYN_LINK")


# Add the GoogleTest library subdirectory
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
add_subdirectory(thirdparty/googletest)


# Add project executable
add_executable(blackjack_academy src/main.cpp src/card_classes.cpp)

# Add the unit test executable
add_executable(test test/utest.cpp src/card_classes.cpp)
# add_executable(test src/main.cpp src/card_classes.cpp)

# target_link_libraries(test 
#     gtest_main
#     pthread
# )

target_link_libraries(blackjack_academy ${Boost_LIBRARIES})

target_link_libraries(test 
    gtest_main
    pthread
    ${Boost_LIBRARIES}
)
