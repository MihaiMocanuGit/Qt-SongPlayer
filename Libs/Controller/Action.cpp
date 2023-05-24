
#include "Action.h"

Action::Action(Repository &ref_repo, Song song) : m_ref_repo{ref_repo}, m_song{std::move(song)}
{

}
