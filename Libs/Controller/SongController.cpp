#include "SongController.h"
#include <algorithm>

void SongController::addSong(const std::string &title, const std::string &artist, const std::string &link,
                             const std::string &lyrics)
{
    Song song(title, artist, link, lyrics);

    try
    {
        m_ref_repository.store(song);
    }
    // I was forced to do this against my will, send help
    catch (std::exception &err)
    {
        throw err;
    }
}

const Song &SongController::findSong(const std::string &title, const std::string &artist)
{
    try
    {
        return m_ref_repository.find(title, artist);
    }
    // I was forced to do this against my will, send help
    catch (std::exception &err)
    {
        throw err;
    }
}

std::vector<Song> SongController::getSongsSortedByTitle(bool decreasing)
{
    std::vector<Song> songs = m_ref_repository.getSongsVector();

    std::sort(songs.begin(), songs.end(), [=](const Song& elem1, const Song& elem2)->bool{
        return (elem1.getTitle().compare(elem2.getTitle()) <= 0) != (decreasing);
    });

    return songs;
}

std::vector<Song> SongController::getSongsSortedByArtist(bool decreasing)
{
    std::vector<Song> songs = m_ref_repository.getSongsVector();

    std::sort(songs.begin(), songs.end(), [=](const Song& elem1, const Song& elem2)->bool{
        return (elem1.getArtist().compare(elem2.getArtist()) <= 0) != (decreasing);
    });

    return songs;
}
