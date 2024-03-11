cmake_minimum_required(VERSION 3.28)
project(lab2 C)

set(CMAKE_C_STANDARD 11)

add_executable(lab2 main.c
        Domain/medicament.c
        Domain/medicament.h
        Validator/validator.c
        Validator/validator.h
        Domain/lista.c
        Domain/lista.h
        Tests/tests.c
        Tests/tests.h
        Service/Service.c
        Service/Service.h
        Ui/Menu.c
        Ui/Menu.h
        Utility/Utility.c
        Utility/Utility.h)
