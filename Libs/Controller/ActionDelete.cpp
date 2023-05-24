
#include "ActionDelete.h"

void ActionDelete::apply()
{
    m_ref_repo.store(m_song);
}
