cmake_minimum_required(VERSION 2.8.12)

project(WordClockQt LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Core Quick REQUIRED)

add_executable(${PROJECT_NAME}
    "main.cpp"
    "wordclock.cpp"
    "qwordclock.cpp"
    "qclockletter.cpp"
    "qml.qrc")

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Quick)
