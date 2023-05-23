#pragma once
#include "Repository.h"

class Playlist : public Repository
{
private:
    static int m_generateRandomNumber(int low, int high);

    static std::vector<int> m_randomIndexes(int noElements);
public:
    Playlist() = default;

    void clear();

    void generateRandom(const SongMap_t &songs, unsigned int size);
    void generateRandom(const std::vector<Song> &songs, unsigned int size);


};
