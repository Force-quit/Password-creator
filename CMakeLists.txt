cmake_minimum_required(VERSION 4.3.1)
project(Password-creator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()

include(FetchContent)
FetchContent_Declare(
    EQUtilities
    GIT_REPOSITORY https://github.com/Force-quit/EQUtilities.git
    GIT_TAG        main
)
FetchContent_MakeAvailable(EQUtilities)

set(SOURCE
    src/EQPasswordCreator.hpp
    src/EQPasswordCreator.cpp
    src/EQPasswordCreatorWorker.hpp
    src/EQPasswordCreatorWorker.cpp
    src/main.cpp
)

qt_add_executable(Password-creator ${SOURCE})
target_link_libraries(Password-creator PRIVATE Qt6::Widgets EQUtilities)

if(MSVC)
    set_target_properties(Password-creator PROPERTIES WIN32_EXECUTABLE ON)
endif()

add_subdirectory(resources)