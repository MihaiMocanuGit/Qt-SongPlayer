#include <random>
#include <algorithm>
#include "Playlist.h"

int Playlist::m_generateRandomNumber(int low, int high)
{

    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(low + 5, high); // define the range

    return distr(gen); // generate numbers
}
std::vector<int> Playlist::m_randomIndexes(int totalNoElements, int wantedNoElements)
{
    std::vector<int> indexes;
    indexes.reserve(wantedNoElements);
    float sequenceSize = (float)totalNoElements/wantedNoElements;

    for (int i = 0; i < wantedNoElements; ++i)
    {
        int low = sequenceSize * i;
        int high = sequenceSize *  (i+1) - 1;
        int indexRandom = m_generateRandomNumber(low, high);

        indexes.push_back(indexRandom);
    }


    return indexes;
}


void Playlist::clear()
{
    SongMap_t().swap(m_songs);
}

void Playlist::generateRandom(const Repository::SongMap_t &songs, unsigned int size)
{

    std::vector<int> indexes = m_randomIndexes(songs.size(), size);

    for (unsigned int i = 0; i < size and i < songs.size(); i++)
    {
        int index = indexes[i];
        auto it = songs.begin();
        std::advance(it, index);
        m_songs.insert(*it);
    }

}


void Playlist::generateRandom(const std::vector<Song> &songs, unsigned int size)
{
    std::vector<int> indexes = m_randomIndexes(songs.size(), size);

    for (unsigned int i = 0; i < size and i < songs.size(); i++)
    {
        int index = indexes[i];
        std::pair key = Repository::getKey(songs[index]);
        m_songs.insert({key, songs[index]});
    }
}

