cmake_minimum_required(VERSION 3.18)

project(NetWork LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX-STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Network REQUIRED)

add_library(${PROJECT_NAME} SHARED
    DllGlobal.hxx
    AbstractSocket.hxx
    AbstractSocket.cxx
    UdpSocket.hxx
    UdpSocket.cxx
)

target_compile_definitions(${PROJECT_NAME} PRIVATE NETWORK_LIBRARY)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core Qt5::Network)
