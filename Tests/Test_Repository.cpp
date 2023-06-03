#include <catch2/catch_all.hpp>
#include "Repository/Repository.h"
#include "Domain/SongException.h"

TEST_CASE( "Repository", "[Repository]")
{
    Song song1("title1", "artist1", "link1", "lyrics1");
    Song song2("title2", "artist2", "link2", "lyrics2");
    Song song3("title3", "artist3", "", "");
    Song song12("title1", "artist2", "link1", "lyrics2");
    SECTION("Store")
    {

        Repository repo;

        REQUIRE(repo.getSongs().empty());

        repo.store(song1);
        REQUIRE(repo.getSongs().size() == 1);
        REQUIRE(repo.getSongs().begin()->second == song1);
        REQUIRE(repo.getSongs().begin()->second == Song(song1.getTitle(), song1.getArtist(), "", ""));

        REQUIRE_THROWS_AS(repo.store(song1), SongException);
        REQUIRE(repo.getSongs().size() == 1);

        repo.store(song2);
        REQUIRE(repo.getSongs().size() == 2);

    }
    Repository repo;
    repo.store(song1);
    repo.store(song2);
    repo.store(song3);
    repo.store(song12);

    REQUIRE(repo.getSongs().size() == 4);
    REQUIRE(repo.getSongs().size() == repo.getSongsVector().size());

    SECTION("find")
    {
        REQUIRE(repo.find(song1.getTitle(), song1.getArtist()) == song1);
        REQUIRE(repo.find(song2.getTitle(), song2.getArtist()) == song2);
        REQUIRE(repo.find(song3.getTitle(), song3.getArtist()) == song3);
        REQUIRE(repo.find(song1.getTitle(), song2.getArtist()) == song12);

        REQUIRE_THROWS_AS(repo.find("Title1", "Artist3"), SongException);
    }

    SECTION("remove")
    {
        repo.remove(song1);
        REQUIRE(repo.getSongs().size() == 3);
        REQUIRE_THROWS_AS(repo.remove(song1), SongException);

        repo.remove(song2);
        REQUIRE(repo.getSongs().size() == 2);
        repo.remove(song3);
        REQUIRE(repo.getSongs().size() == 1);
        repo.remove(song12);
        REQUIRE(repo.getSongs().size() == 0);
    }

    SECTION("get key")
    {
        auto pair = Repository::getKey(song1);
        REQUIRE(pair.first == song1.getTitle());
        REQUIRE(pair.second == song1.getArtist());
    }
}