#include "SongController.h"
#include <algorithm>
#include <iostream>


SongController::SongController(Repository &ref_repository) : m_ref_repository{ref_repository}
{

}


void SongController::addSong(const std::string &title, const std::string &artist, const std::string &link,
                             const std::string &lyrics)
{
    Song song(title, artist, link, lyrics);

    try
    {
        m_ref_repository.store(song);
        m_undoStack.emplace(std::make_unique<ActionAdd>(m_ref_repository, song), m_undoId++);
    }
    // I was forced to do this against my will, send help
    catch (std::exception &err)
    {
        throw err;
    }
}
void SongController::removeSong(const Song& song)
{
    try
    {
        m_ref_repository.remove(song);
        m_undoStack.emplace(std::make_unique<ActionDelete>(m_ref_repository, song), m_undoId++);
    }
    // I was forced to do this against my will, send help
    catch (std::exception &err)
    {
        throw err;
    }

}

void SongController::addToPlaylist(const Song &song)
{
    try
    {
        m_playlist.store(song);
        m_undoStack.emplace(std::make_unique<ActionAdd>(m_playlist, song), m_undoId++);
    }
        // I was forced to do this against my will, send help
    catch (std::exception &err)
    {
        throw err;
    }
}

void SongController::removeFromPlaylist(const Song &song)
{
    try
    {
        m_playlist.remove(song);
        m_undoStack.emplace(std::make_unique<ActionDelete>(m_playlist, song), m_undoId++);
    }
        // I was forced to do this against my will, send help
    catch (std::exception &err)
    {
        throw err;
    }
}

void SongController::generateRandomPlaylist(int noSongs)
{
    Playlist temp;
    temp.generateRandom(m_ref_repository.getSongs(), noSongs);

    for (const auto& songMapElement : temp.getSongs())
    {
        m_playlist.store(songMapElement.second);
        m_undoStack.emplace(std::make_unique<ActionAdd>(m_playlist, songMapElement.second), m_undoId);
    }
    m_undoId++;

}

const Song &SongController::findSong(const std::string &title, const std::string &artist) const
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

const Song &SongController::findSongInPlaylist(const std::string &title, const std::string &artist) const
{
    try
    {
        return m_playlist.find(title, artist);
    }
    // I was forced to do this against my will, send help
    catch (std::exception &err)
    {
        throw err;
    }
}



std::vector<Song> SongController::getSongsSortedByTitle(bool decreasing) const
{
    std::vector<Song> songs = m_ref_repository.getSongsVector();

    std::sort(songs.begin(), songs.end(), [=](const Song& elem1, const Song& elem2)->bool{
        return (elem1.getTitle().compare(elem2.getTitle()) <= 0) != (decreasing);
    });

    return songs;
}

std::vector<Song> SongController::getSongsSortedByArtist(bool decreasing) const
{
    std::vector<Song> songs = m_ref_repository.getSongsVector();

    std::sort(songs.begin(), songs.end(), [=](const Song& elem1, const Song& elem2)->bool{
        return (elem1.getArtist().compare(elem2.getArtist()) <= 0) != (decreasing);
    });

    return songs;
}

void SongController::undo()
{
    if (not m_undoStack.empty())
    {
        unsigned int actionId = m_undoStack.top().second;
        while(m_undoStack.top().second == actionId)
        {
            auto actionPair = std::move(m_undoStack.top());
            m_undoStack.pop();
            m_redoStack.push(std::move(actionPair));

            m_redoStack.top().first->apply();
        }
    }
}

void SongController::redo()
{
    if (not m_redoStack.empty())
    {
        unsigned int actionId = m_redoStack.top().second;
        while(m_redoStack.top().second == actionId)
        {
            auto actionPair = std::move(m_redoStack.top());
            m_redoStack.pop();
            m_undoStack.push(std::move(actionPair));

            m_undoStack.top().first->apply();
        }
    }
}

