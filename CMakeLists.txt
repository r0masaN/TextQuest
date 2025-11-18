cmake_minimum_required(VERSION 3.27)
project(TextQuest)

#[[# статическая линковка всевозможных библиотек, подгружаемых при запуске программы
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -static-libgcc -static-libstdc++")]]

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(
        TextQuest
        main.cpp
        Entities/Item.h
        Entities/Item.cpp
        Entities/Location.h
        Entities/Location.cpp
        Entities/Inventory.h
        Entities/Inventory.cpp
        Entities/House.h
        Entities/House.cpp
        Entities/Game.h
        Entities/Game.cpp
        Entities/Command.h
        Entities/Command.cpp)

#[[include_directories(Entities)]]

# копирование нужных библиотек в папку с билдом, нужные библиотеки нужно узнавать как зависимости .exe файла
#add_custom_command(TARGET TextQuest POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:TextQuest>"
#        COMMAND ${CMAKE_COMMAND} -E copy_if_different
#        "C:/msys64/mingw64/bin/libgcc_s_seh-1.dll"
#        "C:/msys64/mingw64/bin/libstdc++-6.dll"
#        "C:/msys64/mingw64/bin/libwinpthread-1.dll"
#        "$<TARGET_FILE_DIR:TextQuest>")