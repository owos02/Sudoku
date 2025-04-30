cmake_minimum_required(VERSION 3.30)
project(Sudoku VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall -Wextra -Wpedantic ")

if (CMAKE_BUILD_TYPE MATCHES Release)
    message( STATUS "[INFO]: Enable Maximum Optimization")
    add_compile_options(-O3 )
    add_compile_options(-D _RELEASE)
elseif (CMAKE_BUILD_TYPE MATCHES Debug)
    add_compile_options(-D _DEBUG)
endif ()

configure_file(Sudoku.h.in Sudoku.h)

add_executable(${CMAKE_PROJECT_NAME}
        main.cpp
        Application/Application.cpp
        Application/Application.h
)

find_package(SDL2 CONFIG REQUIRED)
target_link_libraries(${CMAKE_PROJECT_NAME}
        PRIVATE
        $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
        $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)

find_package(imgui CONFIG REQUIRED)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE imgui::imgui)

find_package(sdl2-gfx CONFIG REQUIRED)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE SDL2::SDL2_gfx)

find_package(benchmark CONFIG REQUIRED)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE benchmark::benchmark benchmark::benchmark_main)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${PROJECT_BINARY_DIR})
