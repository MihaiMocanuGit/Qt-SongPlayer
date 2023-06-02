
#include "ActionDelete.h"

void ActionDelete::applyUndo()
{
    m_ref_repo.store(m_song);
}
void ActionDelete::applyRedo()
{
    m_ref_repo.remove(m_song);
}
