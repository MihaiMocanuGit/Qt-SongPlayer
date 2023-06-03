#include <fstream>
#include <iostream>
#include "FileRepository.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////PRIVATE/////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::string FileRepository::m_findFirstVariable(const std::string &variable, std::ifstream &ref_inputFile, bool &outFound)
{
    std::string result;
    while(std::getline(ref_inputFile, result) and not result.starts_with(variable));

    outFound = result.length() >= variable.length();

    if(outFound)
    {
        //we remove the variable flag, e.g. ARTIST="
        result.erase(result.begin(), result.begin() + variable.length());

        std::string line;
        //while the line does not end with _"_ right before the "Carriage Return" if it exists, we need to continue reading
        while((result.at(result.length() - 2) != '"' and result.at(result.length() - 1) != '"') and std::getline(ref_inputFile, line) )
            result += ' ' + line;

        //we delete the \r = "Carriage Return" in this case if it exists at the end of the file and append a space
        if (result.at(result.length() - 1) != '"')
            result.erase(result.length() - 1);


        //we remove the last _"_
        result.erase(result.length() - 1);
    }


    return result;
}




Song FileRepository::m_getNextSong(std::ifstream &ref_inputFile)
{
    bool found1, found2, found3, found4;
    std::string artist = m_findFirstVariable(ARTIST_VAR, ref_inputFile, found1);
    std::string title = m_findFirstVariable(TITLE_VAR, ref_inputFile, found2);
    std::string link = m_findFirstVariable(LINK_VAR, ref_inputFile, found3);
    std::string lyrics = m_findFirstVariable(LYRICS_VAR, ref_inputFile, found4);

    if (found1 and found2 and found3 and found4)
        return Song(title, artist, link, lyrics);
    else
        throw std::runtime_error("Could not load song, check format in file!");

}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////PUBLIC//////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void FileRepository::load(const std::string &filepath)
{
    std::ifstream inputFile;
    inputFile.open(filepath);
    if (inputFile.fail())
        throw std::runtime_error("Failed to open file!");

    while (not inputFile.eof())
    {
        try
        {
            store(m_getNextSong(inputFile));
        }
        catch (std::exception &exp)
        {
            std::cerr << exp.what();
            inputFile.close();
        }

    }

    inputFile.close();
}

void FileRepository::save(const std::string &filepath)
{
    std::ofstream outputFile;
    outputFile.open(filepath);
    if (outputFile.fail())
        throw std::runtime_error("Failed to write to file!");

    for (const auto &[key, song] : m_songs)
    {
        std::string artist = ARTIST_VAR + song.getArtist() + "\"\n";
        std::string title = TITLE_VAR + song.getTitle() + "\"\n";
        std::string link = LINK_VAR + song.getLink() + "\"\n";
        std::string lyrics = LYRICS_VAR + song.getLyrics() + "\"\n";

        outputFile << artist << title << link << lyrics;
    }

    outputFile.close();
}
