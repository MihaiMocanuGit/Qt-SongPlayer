#pragma once
#include "Repository.h"

class FileRepository : public Repository
{
private:
    std::string m_filepath;

    static constexpr char ARTIST_VAR[] = "ARTIST=\"";
    static constexpr char TITLE_VAR[] = "TITLE=\"";
    static constexpr char LYRICS_VAR[] = "LYRICS=\"";

    std::string m_findFirstVariable(const std::string &variable, bool &outFound);
    Song m_getNextSong();
public:
    explicit FileRepository(std::string filepath);
    void load();
    void save();

};
