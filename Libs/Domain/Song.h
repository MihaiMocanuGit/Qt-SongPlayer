#pragma once


#include <string>
#include <vector>

class Song
{
private:
    std::string m_artist;

    std::string m_title;
    std::string m_link;

    std::vector<std::string> m_lyrics;

public:
    Song(std::string artist, std::string title, std::string link, const std::string &lyrics);

    const std::string & getArtist() const;
    const std::string & getTitle() const;
    const std::string & getLink() const;
    const std::vector<std::string> & getLyrics() const;

    std::string toString() const;

};