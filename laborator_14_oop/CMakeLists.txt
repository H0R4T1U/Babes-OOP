cmake_minimum_required(VERSION 3.28)
project(laborator_14_oop)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(laborator_14_oop main.cpp
        Domain/Disciplina.h
        Domain/Disciplina.cpp
        Domain/disciplinaValidator.h
        Domain/disciplinaValidator.cpp
        Domain/exception.h
        Domain/Observer.h
        Domain/undo.h
        GUI/cosCRUDGui.h
        GUI/cosCRUDGui.cpp
        GUI/contracteRdonlyGui.h
        GUI/contracteRdonlyGui.cpp
        GUI/disciplinaGui.h
        GUI/disciplinaGui.cpp
        Repository/Repo.h
        Repository/Repo.cpp
        Service/DisciplinaService.h
        Service/DisciplinaService.cpp
        Domain/disciplinaListModel.cpp
        Domain/disciplinaListModel.h
)
target_link_libraries(laborator_14_oop
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

