cmake_minimum_required(VERSION 3.16)
project(DesktopWidgets LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON) 

find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(SOURCES
    src/main.cpp
    src/MainWidget.cpp
    src/BaseWidget.cpp
    src/ColorWidget.cpp
    src/DigitalClockWidget.cpp             # <- Add this line
)

set(HEADERS
    include/MainWidget.h
    include/BaseWidget.h
    include/ColorWidget.h
    include/DigitalClockWidget.h          # <- Add this line
)

add_executable(DesktopWidgets ${SOURCES} ${HEADERS})

target_link_libraries(DesktopWidgets PRIVATE Qt6::Widgets)
target_include_directories(DesktopWidgets PRIVATE ${CMAKE_SOURCE_DIR}/include)

