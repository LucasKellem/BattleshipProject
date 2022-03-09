cmake_minimum_required(VERSION 3.17)
project(Final)

set(CMAKE_CXX_STANDARD 14)

include_directories("C:/mingw/include")
include_directories("C:/mingw64/include")
include_directories("C:/mingw64/x86_64-w64-mingw32/include")

add_executable(Final main.cpp Game.cpp Game.h GameStates.h Board.cpp Board.h User.cpp User.h Coordinate.h Ship.cpp Ship.h BoardStates.h Coordinate.cpp RectangularButton.cpp RectangularButton.h CircularButton.cpp CircularButton.h)

target_link_directories(Final PUBLIC "C:/mingw/lib")
target_link_directories(Final PUBLIC "C:/mingw64/lib")
target_link_directories(Final PUBLIC "C:/mingw64/x86_64-w64-mingw32/lib")

target_link_libraries(Final sfml-graphics sfml-audio sfml-system sfml-window sfml-main)
