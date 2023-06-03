#include <iostream>

#include "Libs/Repository/Repository.h"
#include "Libs/Repository/Playlist.h"
#include "Libs/Controller/SongController.h"
#include <QApplication>
#include "Libs/Ui/MainWindow.h"

int main(int argc, char *argv[])
{

    Repository repo;

    for (int i = 0; i < 14; ++i)
    {
        std::string title = "Title" + std::to_string(i);
        std::string artist = "Artist" + std::to_string(i);
        std::string link = "";
        std::string lyrics = "Lyrics" + std::to_string(i);
        Song song(title, artist, link, lyrics);

        repo.store(song);
    }

    repo.store(Song("Never Gonna Give You Up ", "Rick Astley", "never_gonna.mp4", "We’re no strangers to love\n"
                                                                                        "You know the rules and so do I\n"
                                                                                        "A full commitment’s what I’m thinking of\n"
                                                                                        "You wouldn’t get this from any other guy\n"
                                                                                        "\n"
                                                                                        "I just wanna tell you how I’m feeling\n"
                                                                                        "Gotta make you understand\n"
                                                                                        "\n"
                                                                                        "Never gonna give you up\n"
                                                                                        "Never gonna let you down\n"
                                                                                        "Never gonna run around and desert you\n"
                                                                                        "Never gonna make you cry\n"
                                                                                        "Never gonna say goodbye\n"
                                                                                        "Never gonna tell a lie and hurt you\n"
                                                                                        "\n"
                                                                                        "We’ve known each other for so long\n"
                                                                                        "Your heart’s been aching but you’re too shy to say it\n"
                                                                                        "Inside we both know what’s been going on\n"
                                                                                        "We know the game and we’re gonna play it\n"
                                                                                        "\n"
                                                                                        "And if you ask me how I’m feeling\n"
                                                                                        "Don’t tell me you’re too blind to see\n"
                                                                                        "\n"
                                                                                        "Never gonna give you up\n"
                                                                                        "Never gonna let you down\n"
                                                                                        "Never gonna run around and desert you\n"
                                                                                        "Never gonna make you cry\n"
                                                                                        "Never gonna say goodbye\n"
                                                                                        "Never gonna tell a lie and hurt you" ));


    QApplication a(argc, argv);
    MainWindow w(nullptr, repo);
    w.show();
    return QApplication::exec();

}
