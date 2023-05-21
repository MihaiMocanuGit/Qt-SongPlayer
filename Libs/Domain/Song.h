#pragma once


#include <string>
#include <vector>

class Song
{
protected:
    std::string m_artist;

    std::string m_title;

private:
    std::vector<std::string> m_lyrics;

public:
    Song(std::string artist, std::string title, const std::string &lyrics);

    const std::string & getArtist() const;
    const std::string & getTitle() const;
    const std::vector<std::string> & getLyrics() const;
};