#pragma once
#include "../Repository/Repository.h"

class Action
{
protected:
    Repository &m_ref_repo;
    Song m_song;
public:
    Action(Repository &ref_repo, Song song);
    virtual void apply() = 0;

    virtual ~Action() = default;

};
