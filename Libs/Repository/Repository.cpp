#include "Repository.h"

#include "../Domain/SongException.h"

void Repository::store(const Song &song)
{
    auto [it, success] = m_songs.insert({getKey(song), song});
    if (not success)
        throw SongException("A song "  + song.getTitle() + " by " + song.getArtist() + " already exists");
}

const Song &Repository::find(const std::string &title, const std::string &artist) const
{
    auto it = m_songs.find(std::make_pair(title, artist));
    if (it == m_songs.end())
        throw SongException("The song "  + title + " by " + artist + " does not exist");
    return it->second;
}

void Repository::remove(const Song &song)
{
    unsigned int removedNoElements = m_songs.erase({song.getTitle(), song.getArtist()});
    if (removedNoElements == 0)
        throw SongException("The song "  + song.getTitle() + " by " + song.getArtist() + " does not exist");

}

const Repository::SongMap_t &Repository::getSongs() const
{
    return m_songs;
}

std::vector<Song> Repository::getSongsVector() const
{
    std::vector<Song> songs;
    songs.reserve(m_songs.size());
    for (const auto &[key, song] : m_songs)
        songs.push_back(song);
    return songs;
}

std::pair<std::string, std::string> Repository::getKey(const Song &song)
{
    return std::make_pair(song.getTitle(), song.getArtist());
}

