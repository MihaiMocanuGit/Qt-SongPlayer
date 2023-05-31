#include <iostream>

#include "Libs/Repository/Repository.h"
#include "Libs/Repository/Playlist.h"
#include "Libs/Controller/SongController.h"
#include <QApplication>
#include "Libs/Ui/MainWindow.h"

int main(int argc, char *argv[])
{
    /*
    Repository repo;

    SongController controller(repo);

    controller.addSong("Anna", "By Anna");

    FileRepository fileRepository;
    fileRepository.load("songs.txt");
pana
    SongController fileController(fileRepository);

    Playlist playlist;
    playlist.generateRandom(fileRepository.getSongs(), 10);

    const auto &songs = playlist.getSongs();

    for (const auto &song : songs)
        std::cout << song.first.first << " -\t" << song.first.second << '\n';
    */


    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return QApplication::exec();

    return 0;
}
