cmake_minimum_required(VERSION 3.14)
project(AoC2022 VERSION 0.1.0 LANGUAGES CXX)
set(CXX_STANDARD 23)
set(CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
include_directories(utils)
find_package(Boost 1.8.0 REQUIRED COMPONENTS program_options)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})

include(FetchContent)

FetchContent_Declare(fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG master
)
FetchContent_MakeAvailable(fmt)
find_package(Threads REQUIRED) # for pthread

add_subdirectory(Pruebas)

add_subdirectory(utils)
add_subdirectory(Dia01)
add_subdirectory(Dia02)
add_subdirectory(Dia03)
add_subdirectory(Dia04)
add_subdirectory(Dia05)
add_subdirectory(Dia06)
add_subdirectory(Dia07)
add_subdirectory(Dia08)
add_subdirectory(Dia09)
add_subdirectory(Dia10)
add_subdirectory(Dia11)
add_subdirectory(Dia12)

# add_subdirectory(Dia13)
# add_subdirectory(Dia14)
# add_subdirectory(Dia15)
# add_subdirectory(Dia16)
# add_subdirectory(Dia17)
# add_subdirectory(Dia18)
# add_subdirectory(Dia19)
# add_subdirectory(Dia20)
# add_subdirectory(Dia21)
# add_subdirectory(Dia22)
# add_subdirectory(Dia23)
# add_subdirectory(Dia24)
# add_subdirectory(Dia25)