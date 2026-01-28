#----------------------- base configuration
cmake_minimum_required(VERSION 3.22)    # minimum cmake version
project(nbkit VERSION 1.0.0)            # project name and version

set(CMAKE_CXX_STANDARD 20)              # c++ standard
set(CMAKE_CXX_STANDARD_REQUIRED YES)    # force c++ standard
set(CMAKE_CXX_EXTENSIONS OFF)           # disable compiler-specific extensions

#----------------------- Library Source Files
 # save source files in SRC var
file(GLOB_RECURSE SRC "${CMAKE_CURRENT_SOURCE_DIR}/nbkit/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/nbkit/*.h") 

 # create library from src
add_library(${PROJECT_NAME} ${SRC}) 

# make headers available to consumers
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

#----------------------- Goole tests

# option to enable/disable tests in release
option(BUILD_TESTING "Build the testing tree" OFF)  

if(BUILD_TESTING)

    enable_testing() 
    find_package(GTest REQUIRED)

    # collect all test source files
    file(GLOB_RECURSE TEST_FILES "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp") 

    # create test executable
    add_executable(${PROJECT_NAME}_tests ${TEST_FILES})  

    # link library and Google Test
    target_link_libraries(${PROJECT_NAME}_tests PRIVATE ${PROJECT_NAME} GTest::gtest GTest::gtest_main) 

    # add include directory for test executable
    target_include_directories(${PROJECT_NAME}_tests PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
    
    # add Google Test CMake module path
    list(APPEND CMAKE_MODULE_PATH "${googletest_SOURCE_DIR}/googletest/cmake") 

    # Include Google Test CMake functions
    include(GoogleTest)  

    # Automatically discover and register all tests with CTest
    gtest_discover_tests(${PROJECT_NAME}_tests)  

endif()