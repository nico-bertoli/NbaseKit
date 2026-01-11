#----------------------- CMake Configuration
cmake_minimum_required(VERSION 3.22)  # Minimum CMake version required
project(NbaseKit VERSION 1.0.0)       # Define project name and version

#----------------------- C++ Standard Settings
set(CMAKE_CXX_STANDARD 20)            # Use C++20 standard
set(CMAKE_CXX_STANDARD_REQUIRED YES)  # Fail if c++20 not available
set(CMAKE_CXX_EXTENSIONS OFF)         # Disable compiler-specific extensions

#----------------------- Library Source Files
file(GLOB_RECURSE SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/nbase_kit/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/nbase_kit/*.h")  # Collect all source files recursively
add_library(${PROJECT_NAME} ${SOURCE_FILES})  # Create library from source files
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")  # Make headers available to consumers

#----------------------- Goole tests
option(BUILD_TESTING "Build the testing tree" OFF)  # Option to enable/disable tests (OFF = excluded from release)
if(BUILD_TESTING)
    enable_testing()  # Enable CTest support
    include(FetchContent)  # Include FetchContent module for downloading dependencies
    FetchContent_Declare(googletest GIT_REPOSITORY https://github.com/google/googletest.git GIT_TAG v1.14.0)  # Declare Google Test dependency
    FetchContent_MakeAvailable(googletest)  # Download and configure Google Test
    
    file(GLOB_RECURSE TEST_FILES "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp")  # Collect all test source files
    if(TEST_FILES)
        add_executable(${PROJECT_NAME}_tests ${TEST_FILES})  # Create test executable
        target_link_libraries(${PROJECT_NAME}_tests PRIVATE ${PROJECT_NAME} GTest::gtest GTest::gtest_main)  # Link library and Google Test
        target_include_directories(${PROJECT_NAME}_tests PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")  # Add include directory for test executable
        
        FetchContent_GetProperties(googletest SOURCE_DIR googletest_SOURCE_DIR)  # Get Google Test source directory
        list(APPEND CMAKE_MODULE_PATH "${googletest_SOURCE_DIR}/googletest/cmake")  # Add Google Test CMake module path
        include(GoogleTest)  # Include Google Test CMake functions
        gtest_discover_tests(${PROJECT_NAME}_tests)  # Automatically discover and register all tests with CTest
    endif()
endif()

#----------------------- CPack Configuration
set(CPACK_PACKAGE_NAME "${PROJECT_NAME}")  # Package name
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")  # Package version from project
set(CPACK_GENERATOR "TGZ")  # Generate TGZ archive for binary package
set(CPACK_SOURCE_GENERATOR "TGZ")  # Generate TGZ archive for source package
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Nicolò Bertoli's base kit library")  # Package description
set(CPACK_PACKAGE_VENDOR "Nicolò Bertoli")  # Package vendor
set(CPACK_PACKAGE_CONTACT "nicobertoli.1999@gmail.com")  # Contact email
set(CPACK_PACKAGE_HOMEPAGE_URL "https://github.com/nicobertoli/NbaseKit")  # Homepage URL
set(CPACK_PACKAGE_LICENSE "MIT")  # License type
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}")  # Output package filename
set(CPACK_OUTPUT_FILE_PREFIX "${CMAKE_SOURCE_DIR}/packages")  # Output directory for packages

#----------------------- Installation Rules
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/nbase_kit" DESTINATION .)  # Install library headers and sources
install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt" DESTINATION .)  # Install CMakeLists.txt for consumers
include(CPack)  # Enable CPack package generation
