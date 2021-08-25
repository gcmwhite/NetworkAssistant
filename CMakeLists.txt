cmake_minimum_required(VERSION 3.18)

project(NetworkAssistant LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out)

find_package(Qt5 COMPONENTS Core Quick LinguistTools REQUIRED)

set(TS_FILES NetworkAssistant_zh_CN.ts)

#添加网络模块
add_subdirectory(NetWork/)

add_executable(${PROJECT_NAME}
  main.cxx
  qml.qrc
  ${TS_FILES}
)

target_compile_definitions(NetworkAssistant
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core Qt5::Quick NetWork)

qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
