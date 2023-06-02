#pragma once
#include <unordered_map>

#include "../Domain/Song.h"

class Repository
{
private:
    struct pair_string_hash
    {
        std::size_t operator () (std::pair<std::string, std::string> const &stringPair) const
        {
            return std::hash<std::string>()(stringPair.first + " " + stringPair.second);
        }
    };

public: using SongMap_t = std::unordered_map<std::pair<std::string, std::string>, Song, pair_string_hash>;
protected:
    //std::pair<Title, Artist>
    SongMap_t m_songs;

public:
    Repository() = default;
    virtual ~Repository() = default;

    //disabling the copy of repo
    Repository(const Repository& other) = default;
    Repository operator=(const Repository& right) = delete;

    void store(const Song& song);
    const Song& find(const std::string &title, const std::string &artist) const;
    void remove(const Song& song);

    const SongMap_t &getSongs() const;

    std::vector<Song> getSongsVector() const;

    static std::pair<std::string, std::string> getKey(const Song &song);
};
