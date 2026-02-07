cmake_minimum_required(VERSION 3.28)
project(SamuraiActionGame LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

FetchContent_Declare(
    LDtkLoader
    GIT_REPOSITORY https://github.com/Madour/LDtkLoader
    GIT_TAG 1.5.3.1)
FetchContent_MakeAvailable(LDtkLoader)

include_directories(include)
add_executable(action-game src/main.cpp src/Player.cpp src/Map.cpp src/Game.cpp)
target_compile_features(action-game PRIVATE cxx_std_17)
target_link_libraries(action-game PRIVATE LDtkLoader::LDtkLoader SFML::Graphics)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT action-game)