cmake_minimum_required(VERSION 3.27)
project(Lab5)

set(CMAKE_CXX_STANDARD 17)

add_executable(Lab5 main.cpp
        main.cpp
        Domain/Disciplina.cpp
        Domain/Disciplina.h
        Repository/Repo.cpp
        Repository/Repo.h
        Ui/Console.cpp
        Ui/Console.h
        Validator/Validator.cpp
        Validator/Validator.h
        Service/DisciplinaService.cpp
        Service/DisciplinaService.h
)
