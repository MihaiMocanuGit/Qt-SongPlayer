#pragma once
#include "../Repository/Repository.h"
#include "../Repository/FileRepository.h"

class SongController
{
private:
    Repository &m_ref_repository;
public:
    SongController(Repository &ref_repository);

    void addSong(const std::string &title, const std::string &artist, const std::string &link = "",
                 const std::string& lyrics = "");

    const Song &findSong(const std::string &title, const std::string &artist) const;

    std::vector<Song> getSongsSortedByTitle(bool decreasing = false) const;
    std::vector<Song> getSongsSortedByArtist(bool decreasing = false) const;
};
