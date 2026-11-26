cmake_minimum_required(VERSION 3.16)
project(CatFeedingGame LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MINGW)
    get_filename_component(COMPILER_BIN "${CMAKE_CXX_COMPILER}" DIRECTORY)
    get_filename_component(COMPILER_PREFIX "${COMPILER_BIN}" DIRECTORY)
    list(APPEND CMAKE_PREFIX_PATH "${COMPILER_PREFIX}")
endif()
find_package(SFML 3 COMPONENTS Graphics Window Audio System QUIET)
if(SFML_FOUND)
    message(STATUS "Using installed SFML ${SFML_VERSION}")
else()
    if(MINGW AND CMAKE_CXX_COMPILER MATCHES "ucrt")
        message(FATAL_ERROR
            "SFML 3 was not found in ${COMPILER_PREFIX}.\n"
            "Open the 'MSYS2 UCRT64' terminal (dark blue icon) and run:\n"
            "    pacman -S mingw-w64-ucrt-x86_64-sfml\n"
            "Then in VS Code run 'CMake: Delete Cache and Reconfigure'.")
    endif()
    include(FetchContent)
    set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
    set(SFML_BUILD_NETWORK OFF CACHE BOOL "" FORCE)
    FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.2
        GIT_SHALLOW ON
    )
    FetchContent_MakeAvailable(SFML)
endif()

add_executable(CatFeedingGame
    src/main.cpp
    src/AssetManager.cpp
    src/CatView.cpp
    src/Renderer.cpp
    src/Cat.cpp
    src/DomesticCat.cpp
    src/FatCat.cpp
    src/Food.cpp
    src/FeedingStrategy.cpp
    src/GameState.cpp
)

target_link_libraries(CatFeedingGame PRIVATE SFML::Graphics SFML::Window SFML::Audio SFML::System)

target_compile_definitions(CatFeedingGame PRIVATE ASSET_DIR="${CMAKE_SOURCE_DIR}/assets/")

if(MSVC)
    target_compile_options(CatFeedingGame PRIVATE /W4)
else()
    target_compile_options(CatFeedingGame PRIVATE -Wall -Wextra)
endif()
