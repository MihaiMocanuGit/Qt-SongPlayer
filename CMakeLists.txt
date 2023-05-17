cmake_minimum_required(VERSION 3.25)
project(ProjectOop)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -fsanitize=address")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address")

add_executable(ProjectOop main.cpp Libs/Domain/Song.cpp Libs/Domain/Song.h Libs/Domain/SongException.cpp Libs/Domain/SongException.h Libs/Repository/Repository.cpp Libs/Repository/Repository.h Libs/Repository/FileRepository.cpp Libs/Repository/FileRepository.h Libs/Controller/SongController.cpp Libs/Controller/SongController.h)
