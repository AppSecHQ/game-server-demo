cmake_minimum_required(VERSION 3.16)
project(game-server VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenSSL REQUIRED)
find_package(ZLIB REQUIRED)
find_package(expat REQUIRED)

add_executable(game-server
    src/main.cpp
    src/network/message_handler.cpp
    src/player/player_manager.cpp
    src/config/config_parser.cpp
)

target_link_libraries(game-server OpenSSL::SSL OpenSSL::Crypto ZLIB::ZLIB expat::expat)
