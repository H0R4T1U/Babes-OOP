cmake_minimum_required(VERSION 3.28)
project(Examen)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(Examen main.cpp
        Task.cpp
        Task.h
        Repository.cpp
        Repository.h
        Service.cpp
        Service.h
        Observer.h
        Gui.cpp
        Gui.h
        ferestre.cpp
        ferestre.h)
target_link_libraries(Examen
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

