#pragma once

#include "Action.h"

class ActionAdd : public Action
{
private:

public:
    //inheriting the constructor of runtime_error
    using Action::Action;
    void apply() override;
};
