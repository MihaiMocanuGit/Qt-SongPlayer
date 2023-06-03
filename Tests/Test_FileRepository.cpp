#include <catch2/catch_all.hpp>
#include "Repository/FileRepository.h"

TEST_CASE("File Repository", "[Repository]")
{
    SECTION("Load")
    {
        FileRepository repo;
        REQUIRE_THROWS(repo.load("invalid path"));

        repo.load("testInput.txt");

        REQUIRE(repo.getSongs().size() == 2);

        if (repo.getSongsVector()[0].getTitle() == "Title1")
        {
            REQUIRE(repo.getSongsVector()[0].getTitle() == "Title1");
            REQUIRE(repo.getSongsVector()[0].getArtist() == "Artist1");
            REQUIRE(repo.getSongsVector()[0].getLink() == "Link1");
            REQUIRE(repo.getSongsVector()[0].getLyrics() == "LyricsLine1 LyricsLine2 ");

            REQUIRE(repo.getSongsVector()[1].getTitle() == "Title2");
            REQUIRE(repo.getSongsVector()[1].getArtist() == "Artist2");
            REQUIRE(repo.getSongsVector()[1].getLink() == "Link2");
            REQUIRE(repo.getSongsVector()[1].getLyrics() == "LyricsLine1 LyricsLine2 ");
        }
        else
        {
            REQUIRE(repo.getSongsVector()[1].getTitle() == "Title1");
            REQUIRE(repo.getSongsVector()[1].getArtist() == "Artist1");
            REQUIRE(repo.getSongsVector()[1].getLink() == "Link1");
            REQUIRE(repo.getSongsVector()[1].getLyrics() == "LyricsLine1 LyricsLine2 ");

            REQUIRE(repo.getSongsVector()[0].getTitle() == "Title2");
            REQUIRE(repo.getSongsVector()[0].getArtist() == "Artist2");
            REQUIRE(repo.getSongsVector()[0].getLink() == "Link2");
            REQUIRE(repo.getSongsVector()[0].getLyrics() == "LyricsLine1 LyricsLine2 ");
        }
    }

    SECTION("Save")
    {
        FileRepository repo;
        REQUIRE_THROWS(repo.load("invalid path"));

        repo.load("testInput.txt");
        repo.save("testOutput.txt");

        FileRepository newRepo;
        newRepo.load("testOutput.txt");

        REQUIRE(newRepo.getSongs().size() == 2);
        if (newRepo.getSongsVector()[0].getTitle() == "Title1")
        {
            REQUIRE(newRepo.getSongsVector()[0].getTitle() == "Title1");
            REQUIRE(newRepo.getSongsVector()[0].getArtist() == "Artist1");
            REQUIRE(newRepo.getSongsVector()[0].getLink() == "Link1");
            REQUIRE(newRepo.getSongsVector()[0].getLyrics() == "LyricsLine1 LyricsLine2 ");

            REQUIRE(newRepo.getSongsVector()[1].getTitle() == "Title2");
            REQUIRE(newRepo.getSongsVector()[1].getArtist() == "Artist2");
            REQUIRE(newRepo.getSongsVector()[1].getLink() == "Link2");
            REQUIRE(newRepo.getSongsVector()[1].getLyrics() == "LyricsLine1 LyricsLine2 ");
        }
        else
        {
            REQUIRE(newRepo.getSongsVector()[1].getTitle() == "Title1");
            REQUIRE(newRepo.getSongsVector()[1].getArtist() == "Artist1");
            REQUIRE(newRepo.getSongsVector()[1].getLink() == "Link1");
            REQUIRE(newRepo.getSongsVector()[1].getLyrics() == "LyricsLine1 LyricsLine2 ");

            REQUIRE(newRepo.getSongsVector()[0].getTitle() == "Title2");
            REQUIRE(newRepo.getSongsVector()[0].getArtist() == "Artist2");
            REQUIRE(newRepo.getSongsVector()[0].getLink() == "Link2");
            REQUIRE(newRepo.getSongsVector()[0].getLyrics() == "LyricsLine1 LyricsLine2 ");
        }
    }
}