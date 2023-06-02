#pragma once
#include "../Repository/Repository.h"
#include "../Repository/FileRepository.h"
#include "../Repository/Playlist.h"

#include <memory>
#include <stack>
#include "Action.h"
#include "ActionAdd.h"
#include "ActionDelete.h"

class SongController
{
private:
    Repository &m_ref_repository;
    Playlist m_playlist;


    //we use undoId/redoId to group elementary to have the ability to group elementary actions into a single composed action
    unsigned int m_undoId = 0;
    //std::pair<Action, ActionId>
    std::stack<std::pair<std::unique_ptr<Action>, int>> m_undoStack;

    unsigned int m_redoId = 0;
    std::stack<std::pair<std::unique_ptr<Action>, int>> m_redoStack;
public:
    explicit SongController(Repository &ref_repository);

    void addSong(const std::string &title, const std::string &artist, const std::string &link = "",
                 const std::string& lyrics = "");
    void removeSong(const Song& song);

    void addToPlaylist(const Song& song);
    void removeFromPlaylist(const Song& song);
    void generateRandomPlaylist(int noSongs);

    const Song &findSong(const std::string &title, const std::string &artist) const;
    const Song &findSongInPlaylist(const std::string &title, const std::string &artist) const;

    std::vector<Song> getSongsSortedByTitle(bool decreasing = false) const;
    std::vector<Song> getSongsSortedByArtist(bool decreasing = false) const;

    std::vector<Song> getPlaylistSortedByTitle(bool decreasing = false) const;
    std::vector<Song> getPlaylistSortedByArtist(bool decreasing = false) const;

    const Repository::SongMap_t &getSongs() const;
    const Repository::SongMap_t &getPlaylistSongs() const;

    void undo();
    void redo();

};
