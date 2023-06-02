#include "Song.h"

#include <sstream>
#include <algorithm>
#include <utility>

Song::Song(std::string title, std::string artist, std::string link, const std::string &lyrics)
        :m_title{std::move(title)},  m_artist{std::move(artist)}, m_link{std::move(link)}, m_originalLyrics{lyrics}
{
    m_lyricsWords = std::vector<std::string>();

    std::stringstream ss(lyrics);
    std::string word;
    while (ss >> word)
    {
        erase_if(word, [=](char ch)->bool{return not std::isalpha(ch);});
        std::for_each(word.begin(), word.end(), [=](char &ch){ch = tolower(ch);});

        m_lyricsWords.push_back(word);
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

const std::vector<std::string> & Song::getLyricsWords() const
{
    return m_lyricsWords;
}

const std::string &Song::getLink() const
{
    return m_link;
}
const std::string &Song::getLyrics() const
{
    return m_originalLyrics;
}

std::string Song::toString() const
{
    return m_title + " - " + m_artist;
}

std::vector<std::string> Song::getBackSongAttributes(const std::string &songToString)
{
    unsigned int delimiterPos = songToString.find('-');
    std::string artist = songToString.substr(0, delimiterPos - 1);
    std::string title = songToString.substr(delimiterPos+2, songToString.length());

    std::vector<std::string> attributes = {artist, title, "", ""};
    return attributes;
}


bool Song::operator==(const Song &right)
{
    return this->m_title == right.m_title and this->m_artist == right.m_artist;
}


