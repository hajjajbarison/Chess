#[[
    Autore: MARCO FACCO
]]

cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

project(Chessboard)

include_directories(include)

add_library(chessboard

    include/chessboard.h

    src/chessboard.cpp
    src/promotion.cpp
    src/castling.cpp
    src/movements.cpp
    src/controls.cpp
)

add_library(chess

    include/chess.h
    include/bishop.h
    include/pawn.h
    include/king.h
    include/knight.h
    include/queen.h
    include/rook.h
    include/empty.h

    src/chess.cpp
    src/bishop.cpp
    src/pawn.cpp
    src/king.cpp
    src/knight.cpp
    src/queen.cpp
    src/rook.cpp
)

add_library(position
    include/position.h
    src/position.cpp
)

add_executable(scacchiera
    src/mainChessboard.cpp
)

target_link_libraries(scacchiera
    chessboard
    chess
    position
)

add_executable(replay
    src/mainReplay.cpp
)

target_link_libraries(replay
    chessboard
    chess
    position
)

set(CMAKE_CXX_FLAGS, "-02")
set(CMAKE_CXX_FLAGS_DEBUG, "-02")
set(CMAKE_CXX_FLAGS_RELEASE, "-02")
