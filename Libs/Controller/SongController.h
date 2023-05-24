#pragma once
#include "../Repository/Repository.h"
#include "../Repository/FileRepository.h"
#include <memory>
#include <stack>
#include "Action.h"

class SongController
{
private:
    Repository &m_ref_repository;


    std::stack<std::unique_ptr<Action>> m_undoStack;
    std::stack<std::unique_ptr<Action>> m_redoStack;
public:
    SongController(Repository &ref_repository);

    void addSong(const std::string &title, const std::string &artist, const std::string &link = "",
                 const std::string& lyrics = "");

    const Song &findSong(const std::string &title, const std::string &artist) const;

    std::vector<Song> getSongsSortedByTitle(bool decreasing = false) const;
    std::vector<Song> getSongsSortedByArtist(bool decreasing = false) const;

    void undo();
    void redo();

};
