cmake_minimum_required(VERSION 3.16)
project(DesktopWidgets LANGUAGES CXX)

# ✅ Qt MOC auto-processing
set(CMAKE_AUTOMOC ON)

# ✅ C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ✅ Find Qt
find_package(Qt6 REQUIRED COMPONENTS Widgets)

# ✅ Source files
set(SOURCES
    src/main.cpp
    src/MainWidget.cpp
    src/BaseWidget.cpp
    src/ColorWidget.cpp
    src/DigitalClockWidget.cpp             
    src/ToDoListWidget.cpp
    src/SettingsWidget.cpp
    src/WidgetManager.cpp
    src/WidgetManagerDialog.cpp
    src/CalendarWidget.cpp
    src/ImageWidget.cpp
    src/StickyNoteWidget.cpp
    src/SystemStatsDashboard.cpp
    src/StatArcWidget.cpp
)

# ✅ Header files
set(HEADERS
    include/MainWidget.h
    include/BaseWidget.h
    include/ColorWidget.h
    include/DigitalClockWidget.h
    include/ToDoListWidget.h
    include/SettingsWidget.h
    include/WidgetManager.h
    include/WidgetManagerDialog.h
    include/CalendarWidget.h
    include/StickyNoteWidget.h
    include/ImageWidget.h
    include/SystemStatsDashboard.h
    include/StatArcWidget.h
)

# ✅ Create the executable
add_executable(DesktopWidgets ${SOURCES} ${HEADERS})

# ✅ Link Qt
target_link_libraries(DesktopWidgets PRIVATE Qt6::Widgets)

# ✅ Include headers
target_include_directories(DesktopWidgets PRIVATE ${CMAKE_SOURCE_DIR}/include)
