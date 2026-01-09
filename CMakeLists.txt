# ----------------------- define cmake version
cmake_minimum_required (VERSION 3.22)

# ----------------------- define cmake project
project(NbaseKit VERSION 1.0.0)        

#----------------------- set c++ version
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS OFF) # force strict standard compliance with c++ version

#----------------------- include source files

# include entire folder (CMAKE_CURRENT_SOURCE_DIR punta alla cartella contenente il CMakeLists.txt file)
file(
    GLOB_RECURSE SOURCE_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/NbaseKit/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/NbaseKit/*.h"
)

#----------------------- create executable with PROJECT_NAME from SOURCE_FILES
add_library(${PROJECT_NAME} ${SOURCE_FILES})

#----------------------- set include directories for consumers
# This allows consumers to include headers like <NbaseKit/Matrix.h>
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

#----------------------- cpack support

set(CPACK_PACKAGE_NAME "${PROJECT_NAME}")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_GENERATOR "TGZ")
set(CPACK_SOURCE_GENERATOR "TGZ")

# Metadata
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Nicolò Bertoli's base kit library")
set(CPACK_PACKAGE_VENDOR "Nicolò Bertoli")
set(CPACK_PACKAGE_CONTACT "nicobertoli.1999@gmail.com")
set(CPACK_PACKAGE_HOMEPAGE_URL "https://github.com/nicobertoli/NbaseKit")
set(CPACK_PACKAGE_LICENSE "MIT")

# Package name
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}")

# targz file output location
set(CPACK_OUTPUT_FILE_PREFIX "${CMAKE_SOURCE_DIR}/packages")

install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/NbaseKit" DESTINATION .)
install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt" DESTINATION .)

include(CPack)