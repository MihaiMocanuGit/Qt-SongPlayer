#include <fstream>
#include "FileRepository.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////PRIVATE/////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::string FileRepository::m_findFirstVariable(const std::string &variable, bool &outFound)
{
    std::string result;
    while(std::getline(m_inputFile, result) and not result.starts_with(variable));

    outFound = result.length() >= variable.length();

    if(outFound)
    {
        //we remove the variable flag, e.g. ARTIST="
        result.erase(result.begin(), result.begin() + variable.length());

        std::string line;
        //while the line does not end with _"_ right before the "Carriage Return" if it exists, we need to continue reading
        while((result.at(result.length() - 2) != '"' and result.at(result.length() - 1) != '"') and std::getline(m_inputFile, line) )
            result += ' ' + line;

        //we delete the \r = "Carriage Return" in this case if it exists at the end of the file and append a space
        if (result.at(result.length() - 1) != '"')
            result.erase(result.length() - 1);


        //we remove the last _"_
        result.erase(result.length() - 1);
    }


    return result;
}




Song FileRepository::m_getNextSong()
{
    bool found1, found2, found3;
    std::string artist = m_findFirstVariable(ARTIST_VAR, found1);
    std::string title = m_findFirstVariable(TITLE_VAR, found2);
    std::string lyrics = m_findFirstVariable(LYRICS_VAR, found3);

    if (found1 and found2 and found3)
        return Song(artist, title, lyrics);
    else
        throw std::runtime_error("Could not load song, check format in file!");

}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////PUBLIC//////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

FileRepository::FileRepository(std::string filepath) : m_filepath(std::move(filepath))
{

}

void FileRepository::load()
{
    std::ifstream inputFile;
    inputFile.open(m_filepath);
    if (inputFile.fail())
        throw std::runtime_error("Failed to open file!");


    inputFile.close();
}
