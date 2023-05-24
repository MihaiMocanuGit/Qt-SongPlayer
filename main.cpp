#include <iostream>

#include "Libs/Repository/Repository.h"
#include "Libs/Repository/Playlist.h"
#include "Libs/Controller/SongController.h"


int main()
{
    Repository repo;

    SongController controller(repo);

    controller.addSong("Anna", "By Anna");

    FileRepository fileRepository;
    fileRepository.load("songs.txt");

    SongController fileController(fileRepository);

    Playlist playlist;
    playlist.generateRandom(fileRepository.getSongs(), 10);

    const auto &songs = playlist.getSongs();

    for (const auto &song : songs)
        std::cout << song.first.first << " -\t" << song.first.second << '\n';


    return 0;
}
