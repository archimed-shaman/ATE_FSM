#pragma once

namespace cle
{
namespace fsm
{

class AStateMachine;

class State
{
public:
    virtual State* RunState(AStateMachine *pStateMachine) = 0;
};

} // namespace fsm
} // namespace cle