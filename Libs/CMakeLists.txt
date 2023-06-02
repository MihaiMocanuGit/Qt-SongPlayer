cmake_minimum_required(VERSION 3.24)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_library(Libs
        Controller/SongController.cpp Controller/SongController.h Domain/ActionDelete.cpp Domain/ActionDelete.h
        Domain/Action.cpp Domain/Action.h Domain/Action.cpp Domain/Action.h Domain/ActionAdd.cpp
        Domain/ActionAdd.h
        Domain/Song.cpp Domain/Song.cpp Domain/SongException.cpp Domain/SongException.h
        Repository/Repository.cpp Repository/Repository.h Repository/FileRepository.cpp Repository/FileRepository.h
        Repository/Playlist.cpp Repository/Playlist.h
        Ui/MainWindow.cpp Ui/MainWindow.h)

target_link_libraries(Libs
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        )