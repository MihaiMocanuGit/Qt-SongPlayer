#pragma once

#include "Action.h"

class ActionDelete : public Action
{
private:

public:
    using Action::Action;
    void apply() override;
};
