cmake_minimum_required(VERSION 3.28)
project(muzica2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(muzica2 main.cpp
        Melodie.cpp
        Melodie.h
        Repository.cpp
        Repository.h
        Service.cpp
        Service.h
        Gui.cpp
        Gui.h
        MelodieTableModel.cpp
        MelodieTableModel.h)
target_link_libraries(muzica2
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
)

