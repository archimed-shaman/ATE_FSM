#pragma once

#include "State.h"

namespace cle
{
namespace fsm
{

class AStateMachine
{
public:
    AStateMachine() = default;
    virtual ~AStateMachine() = default;
    virtual void clear() = 0;
    virtual State& getInitialState() = 0;

    virtual State& reset()
    {
        clear();
        return getInitialState();
    }
};

} // namespace fsm
} // namespace cle