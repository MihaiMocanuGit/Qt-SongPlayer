#include "Song.h"

#include <sstream>
#include <algorithm>
#include <utility>

Song::Song(std::string artist, std::string title, std::string link, const std::string &lyrics)
        : m_artist{std::move(artist)}, m_title{std::move(title)}, m_link{std::move(link)}
{
    m_lyrics = std::vector<std::string>();

    std::stringstream ss(lyrics);
    std::string word;
    while (ss >> word)
    {
        erase_if(word, [=](char ch)->bool{return not std::isalpha(ch);});
        std::for_each(word.begin(), word.end(), [=](char &ch){ch = tolower(ch);});

        m_lyrics.push_back(word);
    }
}

const std::string & Song::getArtist() const
{
    return m_artist;
}

const std::string & Song::getTitle() const
{
    return m_title;
}

const std::vector<std::string> & Song::getLyrics() const
{
    return m_lyrics;
}

const std::string &Song::getLink() const
{
    return m_link;
}

std::string Song::toString() const
{
    return m_artist + " - " + m_title;
}
