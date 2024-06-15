cmake_minimum_required(VERSION 3.28)
project(3)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(3 main.cpp
        Produs.cpp
        Produs.h
        Repository.cpp
        Repository.h
        Service.cpp
        Service.h
        Gui.cpp
        Gui.h
        Observer.h
        produsTableModel.cpp
        produsTableModel.h
        produsGui.cpp
        produsGui.h
)
target_link_libraries(3
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

