cmake_minimum_required(VERSION 3.26)
project(Password-creator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(ENV{PATH} "C:/Qt/6.8.1/msvc2022_64/bin;$ENV{PATH}")
set(CMAKE_PREFIX_PATH "C:/Qt/6.8.1/msvc2022_64")
add_compile_options(/EHsc)
find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()

include(FetchContent)
FetchContent_Declare(
    EQUtilities
    URL https://github.com/Force-quit/EQUtilities/archive/refs/tags/v1.0.0.zip
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
target_sources(Password-creator PRIVATE resources/appIcon.rc)
set_target_properties(Password-creator PROPERTIES
    WIN32_EXECUTABLE ON
)

qt_add_resources(Password-creator imageresources
    PREFIX "/images"
    BASE resources
    FILES resources/appIcon.png
)