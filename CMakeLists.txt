cmake_minimum_required(VERSION 3.30)
project(Sudoku VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 23)

configure_file(Sudoku.h.in Sudoku.h)

# [SECTION] Compiler Specifics
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang") # using Clang
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU") # using GCC

    message(STATUS "[INFO]: Enable Aggressive Warnings")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall -Wextra -Wpedantic -pedantic-errors")

    if (CMAKE_BUILD_TYPE MATCHES Release)
        message(STATUS "[INFO]: Set _RELEASE Flag")
        add_compile_options(-D _RELEASE)
        message(STATUS "[INFO]: Enable Maximum Optimization")
        add_compile_options(-O3)

    elseif (CMAKE_BUILD_TYPE MATCHES Debug)
        message(STATUS "[INFO]: Set _DEBUG Flag")
        add_compile_options(-D _DEBUG)
    endif ()
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Intel") # using Intel C++
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC") # using Visual Studio C++

    message(STATUS "[INFO]: Enable Aggressive Warnings")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /WX")

    if (CMAKE_BUILD_TYPE MATCHES Release)
        message(STATUS "[INFO]: Set _RELEASE Flag")
        add_compile_options(-D _RELEASE)

        message(STATUS "[INFO]: Enable Maximum Optimization")
        add_compile_options(/O2)

    elseif (CMAKE_BUILD_TYPE MATCHES Debug)
        message(STATUS "[INFO]: Set _DEBUG Flag")
        add_compile_options(-D _DEBUG)
    endif ()
endif ()

# [SECTION] Find Packages
find_package(SDL2 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(sdl2-gfx CONFIG REQUIRED)
find_package(benchmark CONFIG REQUIRED)

add_executable(${CMAKE_PROJECT_NAME}
        main.cpp
        Application/Application.cpp
        Application/Application.h
        Application/GUI.cpp
        Application/GUI.h
        Application/Algorithm.cpp
        Application/Algorithm.h
        Application/Settings.h
)
# [SECTION] Linking Libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
        PRIVATE
        $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
        $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE imgui::imgui)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE SDL2::SDL2_gfx)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
        benchmark::benchmark
        benchmark::benchmark_main
)

target_include_directories(${CMAKE_PROJECT_NAME}
        PRIVATE
        ${PROJECT_BINARY_DIR}
)
