cmake_minimum_required(VERSION 3.24)
set(CMAKE_CXX_STANDARD 20)

add_library(Libs
        Controller/SongController.cpp Controller/SongController.h
        Domain/Song.cpp Domain/Song.cpp Domain/SongException.cpp Domain/SongException.h
        Repository/Repository.cpp Repository/Repository.h Repository/FileRepository.cpp Repository/FileRepository.h Repository/Playlist.cpp Repository/Playlist.h)