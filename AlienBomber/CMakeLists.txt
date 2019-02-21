# Set project name
project(AlienBomber)
# Define target name
set(TARGET_NAME AlienBomber)

######################################

# Set CMake minimum version and CMake policy required by UrhoCommon module
cmake_minimum_required(VERSION 3.2.3)
if (COMMAND cmake_policy)
    # Libraries linked via full path no longer produce linker search paths
    cmake_policy(SET CMP0003 NEW)
    # INTERFACE_LINK_LIBRARIES defines the link interface
    cmake_policy(SET CMP0022 NEW)
    # Disallow use of the LOCATION target property - so we set to OLD as we still need it
    cmake_policy(SET CMP0026 OLD)
    # MACOSX_RPATH is enabled by default
    cmake_policy(SET CMP0042 NEW)
    # Honor the visibility properties for SHARED target types only
    cmake_policy(SET CMP0063 OLD)
endif ()

# Set CMake modules search path
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake/Modules)

set(CMAKE_CXX_STANDARD 11)

# Include UrhoCommon.cmake module after setting project name
include(UrhoCommon)

# Define source files
define_source_files(
        GLOB_CPP_PATTERNS Source/*.cpp
        GLOB_H_PATTERNS *.hpp Source/*.hpp
        RECURSE true)
# Setup target with resource copying
setup_main_executable()

# Integration with PVS-Studio
include("PVS-Studio")
pvs_studio_add_target(
        TARGET analyze ALL
        OUTPUT FORMAT errorfile
        PREPROCESSOR clang
        ANALYZE AlienBomber
        CXX_FLAGS ${PREPROCESSOR_ADDITIONAL_FLAGS}
        C_FLAGS ${PREPROCESSOR_ADDITIONAL_FLAGS})