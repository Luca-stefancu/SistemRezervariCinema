cmake_minimum_required(VERSION 3.10)
project(SistemRezervariCinema)

find_package(Curses REQUIRED)

add_executable(SistemRezervariCinema
    "SistemRezervariCinema.cpp"
    "Film.cpp"
    "Sala.cpp"
    "Spectacol.cpp"
    "Client.cpp"
    "Rezervare.cpp"
    "Raport.cpp"
 "UI.h" "Storage.h")

target_include_directories(SistemRezervariCinema PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CURSES_INCLUDE_DIR}
)

target_link_libraries(SistemRezervariCinema PRIVATE ${CURSES_LIBRARIES})