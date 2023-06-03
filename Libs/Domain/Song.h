#pragma once


#include <string>
#include <vector>

class Song
{
private:
    std::string m_artist;

    std::string m_title;
    std::string m_link;

    std::string m_originalLyrics;
    std::vector<std::string> m_lyricsWords;

public:
    Song(std::string title, std::string artist, std::string link, const std::string &lyrics);

    const std::string & getArtist() const;
    const std::string & getTitle() const;
    const std::string & getLink() const;
    const std::string & getLyrics() const;
    const std::vector<std::string> & getLyricsWords() const;

    std::string toString() const;
    static std::vector<std::string> getBackSongAttributes(const std::string &songToString);

    bool operator==(const Song& right) const;

};