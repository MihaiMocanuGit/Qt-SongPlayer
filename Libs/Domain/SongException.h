#pragma once
#include <stdexcept>

class SongException : public std::runtime_error
{
private:

public:
    //inheriting the constructor of runtime_error
    using std::runtime_error::runtime_error;


};
