cmake_minimum_required(VERSION 3.28)
project(test)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(test main.cpp
        GUI/DisciplinaGui.cpp
        GUI/DisciplinaGui.h
        Service/DisciplinaService.cpp
        Service/DisciplinaService.h
        Repository/Repo.h
        Repository/Repo.cpp
        Domain/Disciplina.h
        Domain/Disciplina.cpp
        Domain/disciplinaValidator.h
        Domain/disciplinaValidator.cpp
        Domain/exception.h
        Domain/undo.h

)
target_link_libraries(test
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

