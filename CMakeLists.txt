cmake_minimum_required(VERSION 3.28)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

FetchContent_Declare(
  toml11
  GIT_REPOSITORY https://github.com/ToruNiina/toml11.git
  GIT_TAG        v4.1.0
)
FetchContent_MakeAvailable(toml11)

# Include the header files from the "include" directory
include_directories(${PROJECT_SOURCE_DIR}/inc)

# Set the source files
set(SOURCES
    src/main.cpp
    src/MovingCircle.cpp
    src/MovingCircleFactory.cpp
    src/BackgroundDisplay.cpp
    src/Grid.cpp
    src/ConfigReader.cpp
)

# Set the libraries to link
set(LIBRARIES
    sfml-graphics
    toml11::toml11
)

add_executable(main ${SOURCES})
target_link_libraries(main PRIVATE ${LIBRARIES})
target_compile_features(main PRIVATE cxx_std_17)

# Custom command to copy the resources directory to the output directory
add_custom_command(TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:main>/resources
    COMMENT "Copying resources directory to output directory")