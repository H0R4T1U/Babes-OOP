cmake_minimum_required(VERSION 3.28)
project(2)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(2 main.cpp
        Tractor.cpp
        Tractor.h
        Repository.cpp
        Repository.h
        Service.cpp
        Service.h
        Validator.cpp
        Validator.h
        Gui.cpp
        Gui.h
        Observer.h
)
target_link_libraries(2
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

