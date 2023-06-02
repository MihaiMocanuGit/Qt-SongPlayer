#include "ActionAdd.h"

void ActionAdd::applyUndo()
{
    m_ref_repo.remove(m_song);
}

void ActionAdd::applyRedo()
{
    m_ref_repo.store(m_song);
}
