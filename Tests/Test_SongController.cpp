#include <catch2/catch_all.hpp>
#include "Controller/SongController.h"

TEST_CASE("Song Controller", "[SongController]")
{
    Song song1("title1", "artist1", "link1", "lyrics1");
    Song song2("title2", "artist2", "link2", "lyrics2");
    Song song3("title3", "artist3", "", "");
    Song song12("title1", "artist2", "link1", "lyrics2");

    Repository repo;
    repo.store(song1);
    repo.store(song2);
    repo.store(song3);
    repo.store(song12);

    SongController controller(repo);
    SECTION("Sorting")
    {
        SECTION("By title")
        {
            std::vector<Song> songs = controller.getSongsSortedByArtist();

            REQUIRE((songs[0] == song1 or songs[0] == song12));
            REQUIRE(songs[3] == song3);

            songs = controller.getSongsSortedByArtist(true);

            REQUIRE((songs[3] == song1 or songs[3] == song12));
            REQUIRE(songs[0] == song3);
        }
        SECTION("By artist")
        {
            std::vector<Song> songs = controller.getSongsSortedByArtist();

            REQUIRE((songs[0] == song1 or songs[0] == song12));
            REQUIRE(songs[3] == song3);
        }
    }

    SECTION("Playlist")
    {
        REQUIRE_NOTHROW(controller.generateRandomPlaylist(3));
        REQUIRE(controller.getPlaylistSongs().size() == 3);

        REQUIRE_NOTHROW(controller.generateRandomPlaylist(4));
        REQUIRE(controller.getPlaylistSongs().size() == 4);

        REQUIRE_NOTHROW(controller.generateRandomPlaylist(0));
        REQUIRE(controller.getPlaylistSongs().size() == 0);
    }
}